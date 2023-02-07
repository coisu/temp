/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 06:08:49 by jischoi           #+#    #+#             */
/*   Updated: 2023/02/07 07:58:46 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	init_routine(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->mutex_last_eat);
// 	philo->last_eat_time = get_curtime();
// 	pthread_mutex_unlock(&philo->mutex_last_eat);
// 	if ((philo->id - 1) % 2 != 0)
// 		pass_time(philo->arg->time_to_eat, philo->arg);
// }

void    *routine(void *content)
{
    t_philo *philo;

    philo = content;
	pthread_mutex_lock(&philo->mutex_last_eat);
	philo->last_eat_time = get_curtime();
	pthread_mutex_unlock(&philo->mutex_last_eat);
	if ((philo->id - 1) % 2 != 0)
		pass_time(philo->arg->time_to_eat, philo->arg);
    // init_routine(philo);
    if (philo->arg->philo_num > 1)
    {
        while (is_alive(philo->arg))
        {
            print_stat(philo, "is thinking", THINK);
            if (philo->arg->philo_num % 2 != 0 && philo->rotate_count == 0)
            {
                pass_time(philo->arg->time_to_eat, philo->arg);
                philo->rotate_count = philo->arg->philo_num - 1;
            }
            act_eat(philo);
            act_sleep(philo);
        }
    }
    else
        print_stat(philo, "has taken a fork", FORK);
    return (NULL);
}