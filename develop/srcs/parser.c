#include "minishell.h"

extern int	exit_status;

void	*parse_args(char **args, t_prompt *p)
{
	t_token	*tmp;
	int		i;

	p->token = fill_nodes(args);
	if (!p->token)
		return (p);
	tmp = p->token;
	while (tmp->str)
	{
		fill_type(tmp, 0, p);
		if (!tmp->next)
			break;
		tmp = tmp->next;
	}
	exit_status = process(p);
	i = token_countcmd(p->token);
	// print_token(p->token);
	// printf("cmd count : %d\n", i);
	while (i--)
		waitpid(-1, &exit_status, 0); 		//waiting any child process
	return (p);
}

int get_env_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"' || str[i] == ' ' || str[i] == '$')
			break;
		else
			i++;
	}
	return (i);
}

int	jump_env(char *str, int i, int *len, t_prompt *p)
{
	int	env_len;
	int	env_count;
	char *tmp;

	env_len = get_env_len(str + i + 1);
	tmp = get_env(str + i + 1, p->envp, env_len);
	if (tmp)
	{
		env_count = ft_strlen(tmp);
		free (tmp);
		*(len) = *(len) + env_count;
	}
	return (env_len + 1);
}

int manage_double_q(char *str, int q[3], t_prompt *p, int i[2])
{
	while (str[i[0]])
	{
		q[1] = (q[1] + (!q[0] && q[2] % 2 == 0 && str[i[0]] == '\"'));
		if (!q[0] && q[1])
		{
			q[2] = (q[2] + ((q[1] % 2 == 0) && str[i[0]] == '\'')) % 2;
			if (q[1] % 2 != 0)
			{
				if (str[i[0]] == '$')
				{
					i[0] += jump_env(str, i[0], &i[1], p);
					continue;
				}
				else if (str[i[0]] != '\"')
					i[1]++;
			}
			else if (q[1] % 2 == 0)
			{
				if (!q[2] && str[i[0]] == '$')
				{
					i[0] += jump_env(str, i[0], &i[1], p);
					continue;
				}
				else if ((!q[2] && str[i[0]] != '\"' && str[i[0]] != '\'')
					|| (q[2] && str[i[0]] != '\''))
					i[1]++;
			}
		}
		else if (!q[1])
			i[1]++;
		i[0]++;
	}
	return (i[1]);
}
// ERROR CASE :  echo '""'$SHLVL'""'
// ERROR CASE :  echo '"'$SHLVL'"'
int	manage_single_q(char *str, int q[3], t_prompt *p, int i[2])
{
	while(str[i[0]])
	{
		q[0] = (q[0] + (!q[1] && str[i[0]] == '\''));
		if (q[0] && !q[1])
		{
			q[2] = (q[2] + (!q[1] && str[i[0]] == '\"')) % 2;
			if ((q[0] % 2) != 0)
			{
				if (str[i[0]] != '\'')
					i[1]++;
			}
			else if (q[0] % 2 == 0)
			{
				if (str[i[0]] == '$')
				{
					i[0] += jump_env(str, i[0], &i[1], p);
					continue;
				}
				if (str[i[0]] != '\'' && str[i[0]] != '\"') //q[2] && 
					i[1]++;
			}
		}
		else if (!q[0])
			i[1]++;
		i[0]++;
	}
	return (i[1]);
}

int	manage_norm(char *str, t_prompt *p)
{
	int i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i += jump_env(str, i, &len, p);
			continue;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

int	get_len_expand_str(char *str, int q[3], t_prompt *p)
{
	int	i;
	int	tmp[2];

	i = 0;
	tmp[0] = 0;
	tmp[1] = 0;
	while (str[i] && (!q[0] && !q[1]))
	{
		q[0] = (q[0] + (!q[1] && str[i] == '\''));
		q[1] = (q[1] + (!q[0] && str[i] == '\"'));
		i++;
	}
	if (q[0] && !q[1])
	{
		q[0] = 0;
		return (manage_single_q(str, q, p, tmp));
	}
	else if (!q[0] && q[1])
	{
		q[1] = 0;
		return (manage_double_q(str, q, p, tmp));
	}
	else if (!q[0] && !q[1])
		return (manage_norm(str, p));
}

char	*expand_env(char *str, int *i, int *len, t_prompt *p)
{
	int	env_len;
	int	env_count;
	char *tmp;
	int	j;

	j = 0;
	env_len = get_env_len(str + *i + 1);
	tmp = get_env(str + *i + 1, p->envp, env_len);
	if (tmp)
	{
		while (tmp[j])
		{
			p->tmp_rep[*len] = tmp[j];
			(*len)++;
			j++;
		}
		free (tmp);		
	}
	*i += env_len + 1;
	return (p->tmp_rep);
}

char *get_norm_expand(char *str, t_prompt *p, int i[2])
{
	printf("str : %s\n", str);
	while (str[i[0]])
	{
		if (str[i[0]] == '$')
		{
			p->tmp_rep = expand_env(str, &i[0], &i[1], p);
			continue;
		}
		else
		{
			p->tmp_rep[i[1]] = str[i[0]];
			i[1]++;
		}
		i[0]++;
	}
	return (p->tmp_rep);
}

char *get_double_expand(char *str, int q[3], t_prompt *p, int i[2])
{

	while (str[i[0]])
	{
		q[1] = (q[1] + (!q[0] && q[2] % 2 == 0 && str[i[0]] == '\"'));
		if (!q[0] && q[1])
		{
			q[2] = (q[2] + ((q[1] % 2 == 0) && str[i[0]] == '\'')) % 2;
			if (q[1] % 2 != 0)
			{
				if (str[i[0]] == '$')
				{
					p->tmp_rep = expand_env(str, &i[0], &i[1], p);
					continue;
				}
				else if (str[i[0]] != '\"')
					p->tmp_rep[i[1]++] = str[i[0]];
			}
			else if (q[1] % 2 == 0)
			{
				if (!q[2] && str[i[0]] == '$')
				{
					p->tmp_rep = expand_env(str, &i[0], &i[1], p);
					continue;
				}
				else if ((!q[2] && str[i[0]] != '\"' && str[i[0]] != '\'')
					|| (q[2] && str[i[0]] != '\''))
					p->tmp_rep[i[1]++] = str[i[0]];
			}
		}
		else if (!q[1])
			p->tmp_rep[i[1]++] = str[i[0]];
		i[0]++;
	}
	return (p->tmp_rep);
}

char *get_single_expand(char *str, int q[3], t_prompt *p, int i[2])
{

	while(str[i[0]])
	{
		q[0] = (q[0] + (!q[1] && str[i[0]] == '\''));
		if (q[0] && !q[1])
		{
			q[2] = (q[2] + (!q[1] && str[i[0]] == '\"')) % 2;
			if ((q[0] % 2) != 0)
			{
				if (str[i[0]] != '\'')
				{
					p->tmp_rep[i[1]++] = str[i[0]];
				}
			}
			else if (q[0] % 2 == 0)
			{
				if (str[i[0]] == '$')
				{
					p->tmp_rep = expand_env(str, &i[0], &i[1], p);
					continue;
				}
				if ((str[i[0]] != '\'' && str[i[0]] != '\"')) //q[2] && 
					p->tmp_rep[i[1]++] = str[i[0]];
			}
		}
		else if (!q[0])
			p->tmp_rep[i[1]++] = str[i[0]];
		i[0]++;
	}
	return (p->tmp_rep);
}

char *put_str_expand(char *str, int q[3], t_prompt *p)
{
	int	tmp[3];

	tmp[0] = 0;
	tmp[1] = 0;
	q[2] = 0;
	if (q[0] && !q[1])
	{
		q[0] = 0;
		return (get_single_expand(str, q, p, tmp));
	}
	else if (!q[0] && q[1])
	{
		q[1] = 0;
		return (get_double_expand(str, q, p, tmp));
	}
	else if (!q[0] && !q[1])
	{
		return (get_norm_expand(str, p, tmp));
	}
}

char *rep_line(char *str, int q[3], t_prompt *p)
{
	int i;
	int	len;
	char *tmp;

	if (p->tmp_rep)
		free(p->tmp_rep);
	i = 0;
	len = get_len_expand_str(str, q, p);
	p->tmp_rep = malloc(sizeof(char) * (len + 1));
	p->tmp_rep[len] = '\0';
	p->tmp_rep = put_str_expand(str, q, p);
	return (ft_strdup(p->tmp_rep));
}

char	**expand_cmd(char **aux, t_prompt *p)
{
	int		i;
	int		q[3];
	char	*tmp;

	print_env(aux);
	i = 0;
	q[0] = 0;
	q[1] = 0;
	q[2] = 0;
	while (aux[i])
	{
		tmp = aux[i];
		aux[i] = rep_line(aux[i], q, p);
		free (tmp);
		i++;
	}
	// print_env(aux);
	return (aux);
}

char	**ft_fill_array(char **aux, char const *cmd, char *set, int i[3])
{
	int		len;
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	len = ft_strlen(cmd);
	while (cmd[i[0]])
	{
		while (ft_strchr(set, cmd[i[0]]) && cmd[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(set, cmd[i[0]]) || q[0] || q[1]) && cmd[i[0]])
		{
			q[0] = (q[0] + (!q[1] && cmd[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && cmd[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= len)
			aux[i[2]++] = "\0";
		else
			aux[i[2]++] = ft_substr(cmd, i[1], i[0] - i[1]);
	}
	return (aux);
}

    // q[0] = quote
    // q[1] = sin_doub
int ft_count_words(const char *cmd, int q[2])
{
    int i = 0;
    int count = 0;

    while (cmd[i])
    {
        if (cmd[i] != ' ')
        {
            count++;
			while (cmd[i] && (cmd[i] != ' ' || q[0]))
			{
				if (!q[0] && (!q[0] && (cmd[i] == ';' || cmd[i] == '\\')))
					return (-2);
				if (!q[1] && (cmd[i] && (cmd[i] == '\"' || cmd[i] == '\'')))
						q[1] = cmd[i];
				// if (q[0] && !((q[0] + (cmd[i] == q[1])) % 2))
				// 	count++;
				q[0] = (q[0] + (cmd[i] == q[1])) % 2;
				q[1] *= (q[0] != 0);
				i++;
			}
			if (q[0])
				return (-1);
		}
        else
            i++;
    }
    return (count);
}

// int ft_count_words(const char *cmd, int q[2])
// {
//     int quote = 0;
//     int sin_doub = 0;
//     int i = 0;
//     int count = 0;

//     while (cmd[i])
//     {
//         if (cmd[i] != ' ')
//         {
//             count++;
// 			while (cmd[i] && (cmd[i] != ' ' || quote))
// 			{
// 				if (!quote && (!quote && (cmd[i] == ';' || cmd[i] == '\\')))
// 					return (-2);
// 				if (!sin_doub && (cmd[i] && (cmd[i] == '\"' || cmd[i] == '\'')))
// 						sin_doub = cmd[i];
// 				quote = (quote + (cmd[i] == sin_doub)) % 2;
// 				sin_doub *= (quote != 0);
// 				i++;
// 			}
// 			if (quote)
// 				return (-1);
// 		}
//         else
//             i++;
//     }
//     return (count);
// }

char	**ft_cmdtrim(char const *cmd, char *set)
{
	char	**aux;
	int		nwords;
	int		i[3];
	int		q[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	q[0] = 0;
	q[1] = 0;
	if (!cmd)
		return (NULL);
	nwords = ft_count_words(cmd, q);
	if (nwords == -1)
	{
		print_error(QUOTE, (char *)cmd, NULL);
		return (NULL);
	}
	aux = malloc((nwords + 1) * sizeof(char *));
	if (aux == NULL)
		return (NULL);
	aux = ft_fill_array(aux, cmd, set, i);
	aux[nwords] = NULL;
	return (aux);
}

void	*check_args(char *out, t_prompt *p)
{
	char	**cmd;

	if (!out)
	{
		free_matrix(&p->envp);
		printf("exit\n");
		return (NULL);
	}
	if (out[0] != '\0')
		add_history(out);
	cmd = ft_cmdtrim(out, " ");
	free(out);
	if (!cmd)
	{
		exit_status = 22;
		return ("");
	}
	cmd = expand_cmd(cmd, p);
	free(p->tmp_rep);
	p = parse_args(cmd, p);
	return (p);
}
