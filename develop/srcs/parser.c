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

char	*rep_line(char *str, int q[2])
{
	int	i[3];
	char *new;
	char *tmp;

	i[0] = 0;	//normal character end point
	i[1] = 0;	//quote start
	while (str[i[0]])
	{
		// abc"aa'hi'"'bbb'
		while (str[i[0]] != '\'' && str[i[0]] != '\"')
			i[0]++;
		if (i[1] == 0 && i[1] < i[0] - 1)
			new = ft_substr(str, i[0], i[1] - 1);
		i[1] = i[0];

		

		q[0] = (str[i[0]] == '\'');
		q[1] = (str[i[0]] == '\"');
		while ((q[0] || q[1] || str[i[1]] == '\'' || str[i[1]] == '\"') && str[i[0]])
		{
			q[0] = (q[0] + (!q[1] && str[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && str[i[0]] == '\"')) % 2;
			i[0]++;
		}
		manage_single();


	}
	return (new);
}

		// while ((!ft_strchr(set, cmd[i[0]]) || q[0] || q[1]) && cmd[i[0]])
		// {
		// 	q[0] = (q[0] + (!q[1] && cmd[i[0]] == '\'')) % 2;
		// 	q[1] = (q[1] + (!q[0] && cmd[i[0]] == '\"')) % 2;
		// 	i[0]++;
		// }

char	**check_replace_str(char **aux)
{
	int		i;
	int		j;
	int		q[2];
	char	*tmp;

	print_env(aux);
	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (aux[i])
	{
		if (ft_strchr_int(aux[i], '\'') < 0 && ft_strchr_int(aux[i], '\"') < 0)
			i++;
		else
		{
			tmp = aux[i];
			aux[i] = rep_line(aux[i], q);
			free (tmp);
			i++;
		}
	}
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
	aux = check_replace_str(aux);
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
	p = parse_args(cmd, p);
	return (p);
}
