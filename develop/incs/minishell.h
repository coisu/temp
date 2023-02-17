/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:14:04 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/17 05:34:47 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include "libft.h"

# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <limits.h>
# include <errno.h>

# define 	READ	0
# define 	WRITE	1
# define	CHILD	0
# define	SINGLE	1
# define	DOUBLE  2

enum	token_type
{ 
	EMPTY = 0,
	CMD = 1,
	ARG = 2,
	ENV_DEF = 3,
	ENV_VAL = 4,
	OPTN = 5,
	INPUT = 6, // <
	OUTPUT = 7, // >
	DELIM = 8, // <<
	APPEN = 9, // >>
	PIPE = 10
};

enum	e_mini_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 4,
	DUPERR = 5,
	FORKERR = 6,
	PIPERR = 7,
	MEM = 8,
	IS_DIR = 9,
	NOT_DIR = 11,
	OP_NS = 12
};

typedef struct	s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_prompt
{
	t_token	*token;
	t_list	*env;
	char	*tmp_rep;
	char	*result;
	char	**envp;
	int		has_pipe;
	pid_t	pid;
}			t_prompt;

/* temp */
void		print_token(t_token *token);
void		print_env(char **envp);

/* error */
void	*print_error(int err_type, char *cmd, char *param);

/* utils */
void		free_pp(char **pp);
int			token_countcmd(t_token *token);
void 		free_all(t_prompt *p);
int			ft_strchr_int(const char *s, int c);
char		**dup_matrix(char **m);
void		free_matrix(char ***m);
// char		**extend_matrix(char **in, char *newstr);
int			get_matrixlen(char **m);

/* token */
void		token_exception(t_token *token, t_prompt *p);
void		fill_type(t_token *token, int separator, t_prompt *p);
t_token 	*fill_nodes(char **args);

/* expand */
int 		get_env_len(char *str);
int			jump_env(char *str, int i, int *len, t_prompt *p);
char 		*put_str_expand(char *str, int q[3], t_prompt *p);
int			get_len_expand_str(char *str, int q[3], t_prompt *p);
char		**expand_cmd(char **aux, t_prompt *p);

/* parser */
void		*check_args(char *out, t_prompt *p);

/* env */
char		*get_env(char *var, char **envp, int n);
char		**set_env(char *var, char *value, char **envp, int n);

/* main, init */
int			main(int argc, char **argv, char **envp);

/* cmd process */
int 		process(t_prompt *prompt);
t_token		*move_to(t_token *pre, int index);

/* builtin  utils*/
int	ft_print(char *str, t_prompt *prompt);
int	del_envp(int index, t_token *token, t_prompt *prompt);
int	add_envp(char *str, t_prompt *prompt);
int	in_envp(char *token, t_prompt *prompt);
int	update_oldpwd(t_prompt *prompt);

/* builtin  func*/
int			ft_pwd(t_prompt *prompt);
int			ft_cd(int i, t_prompt *prompt);
int			ft_echo(int i, t_prompt *prompt);
int			ft_export(int i, t_prompt *prompt);
int			ft_unset(int i, t_prompt *prompt);
#endif
