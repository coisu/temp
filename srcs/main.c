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
// argv를 구조체에 저장하고 필요한 변수들을 할당하고 초기화해준다
	
	errno = ft_philo_init(&philo, &arg);
	if (errno)
		return (print_error("error philo init", errno));
// 철학자별로 들어갈 변수들을 초기화한다.

	errno = ft_philo_start(&arg, philo);
	if (errno)
		return (print_error("error philo start", errno));
// 철학자를 시작하고 종료될때까지 동작한다
	return (0);
}