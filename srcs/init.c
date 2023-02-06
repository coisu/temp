#include "philo.h"

int	ft_philo_init(t_philo **philo, t_arg *arg)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * arg->philo_num);
	if (!(philo))
		return (1);
	while (i < arg->philo_num)
	{
		(*philo)[i].arg = arg;
		(*philo)[i].num = i;
		(*philo)[i].left = i;
        // (*philo)[i].left = &(arg->forks[i]);
		(*philo)[i].right = (i + 1) % arg->philo_num;
        // (*philo)[i].right = &(arg->forks[(i + 1) % arg->philo_num]);
		(*philo)[i].last_eat_time = ft_get_time();
		// (*philo)[i].last_eat_time = arg->start_time;
		(*philo)[i].eat_count = 0;
		i++;
	}
	return (0);
}

int	ft_arg_init_mutex(t_arg *arg)
{
	int	i;

	if (pthread_mutex_init(&(arg->print), NULL))
		return (1);
	arg->forks = malloc(sizeof(pthread_mutex_t) * arg->philo_num);
	if (!(arg->forks))
		return (1);
	i = 0;
// 철학자의 현재 상태 표시를 섞이게 나오면 안되므로 출력 권한에 뮤텍스 부여
	while (i < arg->philo_num)
	{
		if (pthread_mutex_init(&(arg->forks[i]), NULL))
			return (1);
		i++;
	}
	return (0);
}

int	ft_arg_init(t_arg *arg, int argc, char *argv[])
{
	arg->philo_num = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	arg->start_time = ft_get_time();
	arg->finished_eat = 0;
    arg->finish = 0;
	arg->num_must_eat = 0;
	if (arg->philo_num <= 0 || arg->time_to_die == 0 || arg->time_to_eat == 0
		|| arg->time_to_sleep == 0)
		return (5);
	if (argc == 6)
	{
		arg->num_must_eat = ft_atoi(argv[5]);
		if (arg->num_must_eat <= 0)
			return (6);
	}
	if (ft_arg_init_mutex(arg))
		return (1);
	return (0);
}