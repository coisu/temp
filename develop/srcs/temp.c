#include "minishell.h"

void	print_token(t_token *token)
{
	int	i;

	i = 1;
	printf("======print_token======\n");
	while (token->str)
	{
		printf("%d ) STR : %15s  TYPE : %d  \n", i++, token->str, token->type);
		if (!token->next)
			break;
		token = token->next;
	}
	printf("======print_token======\n");
}

void	print_env(char **envp)
{
	int i;

	i = -1;
	printf("======print_env======\n");
	while(envp[++i])
		printf("%d : %s\n", i + 1, envp[i]);
	printf("======print_env======\n");
}



// char *rep_line(char *str, int q[3], t_prompt *p)
// {
// 	int i[2];
// 	// int	len;

// 	i[0] = 0;
// 	i[1] = 0;
// 	while (str[i[0]])
// 	{
// 		q[0] = (q[0] + (!q[1] && str[i[0]] == '\''));
// 		q[1] = (q[1] + (!q[0] && str[i[0]] == '\"'));
// 		if (q[0] && !q[1])
// 		{
// 			q[2] = (q[2] + (!q[1] && str[i[0]] == '\"')) % 2;
// 			if ((q[0] % 2) != 0)
// 			{
// 				if (str[i[0]] != '\'')
// 					i[1]++;
// 			}
// 			else
// 			{
// 				if (str[i[0]] == '$')
// 				{
// 					i[0] += jump_env(str, i[0], &i[1], p);
// 					continue;
// 				}
// 				if (q[2] && str[i[0]] != '\'' && str[i[0]] != '\"')
// 					i[1]++;
// 			}
// 		}
		
// 		else if (!q[0] && q[1])
// 		{
// 			q[2] = (q[2] + ((q[1] % 2 == 0) && str[i[0]] == '\'')) % 2;
// 			if (q[1] % 2 != 0)
// 			{
// 				if (str[i[0]] == '$')
// 				{
// 					i[0] += jump_env(str, i[0], &i[1], p);
// 					continue;
// 				}
// 				else if (str[i[0]] != '\"')
// 					i[1]++;
// 			}
// 			else
// 			{
// 				if (!q[2] && str[i[0]] == '$')
// 				{
// 					i[0] += jump_env(str, i[0], &i[1], p);
// 					continue;
// 				}
// 				else if (!q[2] && str[i[0]] != '\"' && str[i[0]] != '\'')
// 					i[1]++;
// 				else if (q[2] && str[i[0]] != '\'')
// 					i[1]++;
// 			}
// 		}
// 		else if (!q[0] && !q[1])
// 			i[1]++;
// 		i[0]++;
// 	}
// 	printf("total len : %d\n", i[1]);
// 	return (str);
// }


// char *rep_line(char *str, int q[3], t_prompt *p)
// {
// 	int i;
// 	int	env_len;
// 	int	len;
// 	int	env_count;
// 	char *tmp;

// 	len = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		q[0] = (q[0] + (!q[1] && str[i] == '\''));
// 		q[1] = (q[1] + (!q[0] && str[i] == '\"'));
// 		// printf("single quote : %d double quote : %d\n", q[0], q[1]);
// 		if (q[0] && !q[1])
// 		{
// 			q[2] = (q[2] + (!q[1] && str[i] == '\"')) % 2;
// 			if ((q[0] % 2) != 0)
// 			{
// 				if (str[i] != '\'')
// 					len++;
// 			}
// 			else
// 			{
// 				if (str[i] == '$')
// 				{
// 					env_len = get_env_len(str + i + 1);
// 					tmp = get_env(str + i + 1, p->envp, env_len);
// 					if (tmp)
// 					{
// 						env_count = ft_strlen(tmp);
// 						free (tmp);
// 						len += env_count;
// 					}
// 					i += (env_len + 1);
// 					continue;
// 				}
// 				if (q[2] && str[i] != '\'' && str[i] != '\"')
// 					len++;
// 			}
// 		}
		
// 		else if (!q[0] && q[1])
// 		{
// 			q[2] = (q[2] + ((q[1] % 2 == 0) && str[i] == '\'')) % 2;
// 			printf("double quote : %d inner single quote : %d\n", q[1], q[2]);
// 			printf("	> str[%d] : %c - len : %d\n", i, str[i], len);
// 			if (q[1] % 2 != 0)
// 			{
// 				if (str[i] == '$')
// 				{
// 					env_len = get_env_len(str + i + 1);
// 					tmp = get_env(str + i + 1, p->envp, env_len);
// 					if (tmp)
// 					{
// 						env_count = ft_strlen(tmp);
// 						free (tmp);
// 						len += env_count;
// 					}
// 					i += (env_len + 1);
// 					continue;
// 				}
// 				else if (str[i] != '\"')
// 					len++;
// 			}
// 			else
// 			{
// 				if (!q[2] && str[i] == '$')
// 				{
// 					env_len = get_env_len(str + i + 1);
// 					tmp = get_env(str + i + 1, p->envp, env_len);
// 					if (tmp)
// 					{
// 						env_count = ft_strlen(tmp);
// 						free (tmp);
// 						len += env_count;
// 					}
// 					i += (env_len + 1);
// 					continue;
// 				}
// 				else if (!q[2] && str[i] != '\"' && str[i] != '\'')
// 				{
// 					len++;
// 				}
// 				else if (q[2] && str[i] != '\'')
// 				{
// 					len++;
// 				}
// 			}
// 		}
// 		i++;
// 	}
// 	printf("total len : %d\n", len);
// 	return (str);
// }
