/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 06:08:53 by jischoi           #+#    #+#             */
/*   Updated: 2023/02/07 07:14:20 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool  is_dead(t_arg *arg, int i)
{
    uint64_t    now;
    uint64_t    last;

    pthread_mutex_lock(&arg->philo[i].mutex_last_eat);
    now = get_curtime();
    last = arg->philo[i].last_eat_time;
    if (last && now - last >= arg->time_to_die)
    {
        pthread_mutex_unlock(&arg->philo[i].mutex_last_eat);
        return (1);
    }
    pthread_mutex_unlock(&arg->philo[i].mutex_last_eat);
    return (0);
}

t_bool	is_alive(t_arg *arg)
{
	t_bool	alive;

	pthread_mutex_lock(&arg->mutex_alive);
	alive = arg->alive;
	pthread_mutex_unlock(&arg->mutex_alive);
	return (alive);
}

uint64_t	get_curtime(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	pass_time(uint64_t wait, t_arg *arg)
{
	uint64_t	start;

	start = get_curtime();
	while (get_curtime() - start < wait && is_alive(arg))
		usleep(1);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		ans;
	int		sign;

	i = 0;
	ans = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] > 8 && nptr[i] < 14))
		i += 1;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		sign = 44 - nptr[i];
		i += 1;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		ans *= 10;
		ans = ans + nptr[i] - 48;
		i += 1;
	}
	return (ans * sign);
}