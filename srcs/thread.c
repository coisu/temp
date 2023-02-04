#include "philo.h"


static void	ft_free_thread(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->philo_num)
	{
		pthread_mutex_destroy(&(arg->forks[i++]));
		free(arg->philo);
	}
	pthread_mutex_destroy(&(arg->print));
	free(arg->forks);
}

void	ft_philo_check_finish(t_arg *arg, t_philo *philo)
{
	int			i;
	uint64_t	now;

	while (!arg->finish)
	{
		if ((arg->num_must_eat != 0) && (arg->philo_num == arg->finished_eat))
		{
			arg->finish = 1;
			printf("Every philosophers finished their meal.\n");
			break ;
		}
		i = 0;
		while (i < arg->philo_num)
		{
			now = ft_get_time();
			if ((now - philo[i].last_num_must_eat) >= arg->time_to_die)
			{
				printf("PHILO : %d >>       NOW  : %lu\n\t\t   LAST : %lu\n\t DEAD CONT : %lu\n",philo->num, now, philo[i].last_num_must_eat, now - philo[i].last_num_must_eat);
				ft_philo_printf(arg, i, "died");
				arg->finish = 1;
				break ;
			}
			i++;
		}
	}
}

void	*ft_thread(void *argv)
{
	t_arg		*arg;
	t_philo		*philo;

	philo = argv;
	arg = philo->arg;
	if (philo->num % 2)
		usleep(500 * arg->time_to_eat);
	while (!arg->finish)
	{
		ft_philo_action(arg, philo);
		if (arg->num_must_eat == philo->eat_count)
		{
			arg->finished_eat++;
			break ;
		}
		ft_philo_printf(arg, philo->num, "is sleeping");
		ft_pass_time(arg->time_to_sleep, arg);
		ft_philo_printf(arg, philo->num, "is thinking");
	}
		// if (philo->num % 2 == 0)
	// usleep(50000);
	// if (!arg->finish)
	// 	ft_philo_check_finish(arg, philo);
	return (0);
}

int	ft_philo_start(t_arg *arg, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < arg->philo_num)
	{	
		philo[i].last_num_must_eat = ft_get_time();
		if (pthread_create(&(philo[i].thread), NULL, ft_thread, &(philo[i])))
			return (1);
		i++;
		// i += 2;
		// ft_philo_check_finish(arg, philo);
	}
	// i = 1;
	// while (i < arg->philo_num)
	// {	
	// 	philo[i].last_num_must_eat = ft_get_time();
	// 	if (pthread_create(&(philo[i].thread), NULL, ft_thread, &(philo[i])))
	// 		return (1);
	// 	i += 2;
	// 	// ft_philo_check_finish(arg, philo);
	// }
	usleep(8000);
	if (!arg->finish)
		ft_philo_check_finish(arg, philo);
	i = 0;
	while (i < arg->philo_num)
		pthread_join(philo[i++].thread, NULL);
// 조인을 안하면 프로그램이 먼저 종료되서 쓰레드가 진행되지 않는다.
	ft_free_thread(arg);
	return (0);
}









// static void	ft_free_thread(t_arg *arg)
// {
// 	int	i;

// 	i = 0;
// 	while (i < arg->philo_num)
// 	{
// 		pthread_mutex_destroy(&(arg->forks[i++]));
// 		free(arg->philo);
// 	}
// 	pthread_mutex_destroy(&(arg->print));
// 	free(arg->forks);
// }

// void	ft_philo_check_finish(t_arg *arg, t_philo *philo)
// {
// 	int			i;
// 	uint64_t	now;

// 	while (!arg->finish)
// 	{
// 		if ((arg->num_must_eat != 0) && (arg->philo_num == arg->finished_eat))
// 		{
// 			arg->finish = 1;
// 			printf("Every philosophers finished their meal.\n");
// 			break ;
// 		}
// 		i = 0;
// 		while (i < arg->philo_num)
// 		{
// 			now = ft_get_time();
// 			if ((now - philo[i].last_num_must_eat) >= arg->time_to_die)
// 			{
// 				printf("NOW  : %lu\nLAST : %lu\nDEAD CONT : %lu\n", now, philo[i].last_num_must_eat, now - philo[i].last_num_must_eat);
// 				ft_philo_printf(arg, i, "died");
// 				arg->finish = 1;
// 				break ;
// 			}
// 			i++;
// 		}
// 	}
// }

// void	*ft_thread(void *argv)
// {
// 	t_arg		*arg;
// 	t_philo		*philo;

// 	philo = argv;
// 	arg = philo->arg;
// 	if (philo->num % 2)
// 		usleep(500 * arg->time_to_eat);
// 	while (!arg->finish)
// 	{
// 		ft_philo_action(arg, philo);
// 		if (arg->num_must_eat == philo->eat_count)
// 		{
// 			arg->finished_eat++;
// 			break ;
// 		}
// 		ft_philo_printf(arg, philo->num, "is sleeping");
// 		ft_pass_time(arg->time_to_sleep, arg);
// 		ft_philo_printf(arg, philo->num, "is thinking");
// 	}
// 		// if (philo->num % 2 == 0)
// 		// usleep(500 * arg->time_to_eat);
// 	return (0);
// }

// int	ft_philo_start(t_arg *arg, t_philo *philo)
// {
// 	int		i;

// 	i = 0;
// 	while (i < arg->philo_num)
// 	{	
// 		philo[i].last_num_must_eat = ft_get_time();
// 		if (pthread_create(&(philo[i].thread), NULL, ft_thread, &(philo[i])))
// 			return (1);
// 		i += 2;
// 		// ft_philo_check_finish(arg, philo);
// 	}
// 	i = 1;
// 	while (i < arg->philo_num)
// 	{	
// 		philo[i].last_num_must_eat = ft_get_time();
// 		if (pthread_create(&(philo[i].thread), NULL, ft_thread, &(philo[i])))
// 			return (1);
// 		i += 2;
// 		// ft_philo_check_finish(arg, philo);
// 	}
// 	usleep(8000);
// 	ft_philo_check_finish(arg, philo);
// 	i = 0;
// 	while (i < arg->philo_num)
// 		pthread_join(philo[i++].thread, NULL);
// // 조인을 안하면 프로그램이 먼저 종료되서 쓰레드가 진행되지 않는다.
// 	ft_free_thread(arg);
// 	return (0);
// }

