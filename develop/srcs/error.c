#include "minishell.h"

void	*print_error(int err_type, char *cmd, char *param)
{
	ft_putstr_fd(cmd, 2);
	// write(1, ft_itoa(eorr_type), 1);
	if (err_type == QUOTE)
		write(1, ": \e[91mUnclosed quote\e[0m", 26);
		// ft_putstr_fd("Quote error", 1); 

	// prompt->exit_status = err;
	// if (err_type == QUOTE)
	// 	ft_putstr_fd("Quote error", 2); 
    // else if (err_type == WCHAR)
	// 	ft_putstr_fd("Wrong input character: ", 2);
	else if (err_type == OP_NS)
		ft_putstr_fd(": Old Path not set.", 2);
	else if (err_type == NDIR)
		ft_putstr_fd(": No such file or directory: ", 2);
	// else if (err_type == NPERM)
	// 	ft_putstr_fd("Permission denied: ", 2);
	else if (err_type == NCMD)
		write(1, ": \e[91mCommand not found\e[0m", 29);
	// else if (err_type == DUPERR)
	// 	ft_putstr_fd("Dup failed", 2);
	// else if (err_type == FORKERR)
	// 	ft_putstr_fd("Fork failed", 2);
	// else if (err_type == PIPERR)
	// 	ft_putstr_fd("Pipe error", 2);
	// else if (err_type == MEM)
	// 	ft_putstr_fd("No memory left on device", 2);
	// else if (err_type == IS_DIR)
	// 	ft_putstr_fd("Is a directory: ", 2);
	else if (err_type == NOT_DIR)
		write(1, ": Not a directory", 18);
	ft_putendl_fd(param, 2);
	// return (NULL);
}