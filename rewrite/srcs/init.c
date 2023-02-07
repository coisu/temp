/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 06:08:42 by jischoi           #+#    #+#             */
/*   Updated: 2023/02/07 08:58:11 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_max(int first, int sec)
{
	if (first > sec)
		return (first);
	return (sec);
}

int	ft_min(int first, int sec)
{
	if (first < sec)
		return (first);
	return (sec);
}

static t_philo  *init_philo(int num, t_arg *arg)
{
    t_philo *philo;
    int     i;

    philo = malloc(sizeof(t_philo) * num);
    if (!philo)
        return (NULL);
    i = 0;
    while (i < num)
    {
        philo[i].id = i + 1;
        philo[i].thread_start_time = get_curtime();
        philo[i].last_eat_time = 0;
        philo[i].eat_count = 0;
        philo[i].arg = arg;
        philo[i].left = ft_min(i, (i + 1) % num);
		philo[i].right = ft_max(i, (i + 1) % num);
        // philo[i].right = i;
        // philo[i].left = (i + 1) % arg->philo_num;
        		// printf("philo %d : L - %d R - %d\n", i , philo[i].left, philo[i].right);

        if (i % 2 == 0)
            philo[i].rotate_count = arg->philo_num - i - 1;
        else
            philo[i].rotate_count = arg->philo_num - i - 2;
        pthread_mutex_init(&philo[i].mutex_last_eat, NULL);
        pthread_mutex_init(&philo[i].mutex_eat_count, NULL);
        i++;
    }
    return (philo);
}

static pthread_mutex_t	*init_fork(int num)
{
	pthread_mutex_t	*fork;
	int				i;

	fork = malloc(sizeof(pthread_mutex_t) * (num));
	if (!fork)
		return (NULL);
	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	return (fork);
}

void    init_arg(t_arg *arg, int argc, char **argv)
{
    arg->philo_num = ft_atoi(argv[1]);
    arg->time_to_die = ft_atoi(argv[2]);
    arg->time_to_eat = ft_atoi(argv[3]);
    arg->time_to_sleep = ft_atoi(argv[4]);
    arg->must_eat = -1;
    if (argc > 5)
        arg->must_eat = ft_atoi(argv[5]);
    arg->alive = TRUE;
    arg->fork = init_fork(arg->philo_num);
    pthread_mutex_init(&arg->mutex_alive, NULL);
    pthread_mutex_init(&arg->mutex_print, NULL);
    arg->philo = init_philo(arg->philo_num, arg);
}