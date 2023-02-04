#include "philo.h"


void	ft_pass_time(uint64_t  wait_time, t_arg *arg)
{
	uint64_t	start;
	uint64_t	now;

	start = ft_get_time();
	while (!(arg->finish))
	{
		now = ft_get_time();
		if ((now - start) >= wait_time)
		{
			// printf("NOW : %lu  (now - start) : %lu\n", now, (now - start));
			break ;
		}
		usleep(10);
	}
}

int	ft_philo_printf(t_arg *arg, int num, char *msg)
{
	uint64_t	now;

	now = ft_get_time();
	printf("print LOCK_START\n");
	pthread_mutex_lock(&(arg->print));
	printf("print LOCK_END\n");
	if (!(arg->finish) || (arg->finish && arg->philo_num == 1))
		printf("%7lu %d %s\n", now - arg->start_time, num + 1, msg);
	printf("print UNLOCK_START\n");
	pthread_mutex_unlock(&(arg->print));
	printf("print UNLOCK_END\n");
	return (0);
}

int	ft_philo_action(t_arg *arg, t_philo *philo)
{
	printf("left LOCK_START\n");
	pthread_mutex_lock(philo->left);
	printf("left LOCK_END\n");
	ft_philo_printf(arg, philo->num, "has taken a fork");
	if (arg->philo_num > 1)
	{
		printf("right LOCK_START\n");
		pthread_mutex_lock(philo->right);
		printf("left LOCK_END\n");
		ft_philo_printf(arg, philo->num, "has taken a fork");
		ft_philo_printf(arg, philo->num, "is eating");
		philo->last_num_must_eat = ft_get_time();
		while (!arg->mutex)
			usleep(0);
		printf("check UNLOCK_START\n");
		printf("----arg->mutex: %d\n", arg->mutex);
		pthread_mutex_unlock(&(arg->check));
		printf("check UNLOCK_END\n");
		printf("PHILO : %d -> LAST : %lu\n", philo->num, philo->last_num_must_eat);
		philo->eat_count++;
		ft_pass_time(arg->time_to_eat, arg);
		printf("right UNLOCK_START\n");
		pthread_mutex_unlock(philo->right);
		printf("right UNLOCK_END\n");
	}
	else
	{
		arg->finish = 1;
		ft_philo_printf(arg, philo->num, "died");
	}
	printf("left UNLOCK_START\n");
	pthread_mutex_unlock(philo->left);
	printf("left UNLOCK_END\n");
	return (0);
}



// void	ft_pass_time(uint64_t  wait_time, t_arg *arg)
// {
// 	uint64_t	start;
// 	uint64_t	now;

// 	start = ft_get_time();
// 	while (!(arg->finish))
// 	{
// 		now = ft_get_time();
// 		if ((now - start) >= wait_time)
// 		{
// 			printf("NOW : %lu  (now - start) : %lu\n", now, (now - start));
// 			break ;
// 		}
// 		usleep(10);
// 	}
// }

// int	ft_philo_printf(t_arg *arg, int num, char *msg)
// {
// 	uint64_t	now;

// 	now = ft_get_time();
// 	pthread_mutex_lock(&(arg->print));
// 	if (!(arg->finish))
// 		printf("%7lu %d %s\n", now - arg->start_time, num + 1, msg);
// 	pthread_mutex_unlock(&(arg->print));
// 	return (0);
// }

// int	ft_philo_action(t_arg *arg, t_philo *philo)
// {
// 	pthread_mutex_lock(philo->left);
// 	ft_philo_printf(arg, philo->num, "has taken a fork");
// 	if (pthread_mutex_lock(philo->right) == 0)
// 	{
// 		// pthread_mutex_lock(philo->right);
// 		ft_philo_printf(arg, philo->num, "has taken a fork");
// 		ft_philo_printf(arg, philo->num, "is eating");
// 		philo->last_num_must_eat = ft_get_time();
// 		printf("PHILO : %d -> LAST : %lu\n", philo->num, philo->last_num_must_eat);
// 		philo->eat_count++;
// 		ft_pass_time(arg->time_to_eat, arg);
// 		pthread_mutex_unlock(philo->right);
// 	}
// 	// else
// 	// 	arg->finish = 1;
// 	write(1, "HERE\n", 5);
// 	pthread_mutex_unlock(philo->left);
// 	return (0);
// }