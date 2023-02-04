#include "philo.h"

int	print_usage(int exit_return)
{
	printf(CYAN"Usage: ./philo [num_philos] [time_die] [time_eat]"\
		" [time_sleep] ([num_each_philos_eat])\n"RESET);
	return (exit_return);
}

int print_error(char *str, int stat)
{
    printf("%s\n", str);
    return (stat);
}

int	main(int argc, char *argv[])
{
	t_arg	arg;
	t_philo	*philo;
	int		errno;

	if (argc != 5 && argc != 6)
		return (print_usage(3));

	memset(&arg, 0, sizeof(t_arg));
	errno = ft_arg_init(&arg, argc, argv);
	if (errno)
		return (print_error("error arg init", errno));	
	errno = ft_philo_init(&philo, &arg);
	if (errno)
		return (print_error("error philo init", errno));
	errno = ft_philo_start(&arg, philo);
	if (errno)
		return (print_error("error philo start", errno));
	return (0);
}