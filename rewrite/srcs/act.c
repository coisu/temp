/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 06:08:35 by jischoi           #+#    #+#             */
/*   Updated: 2023/02/07 08:35:57 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_stat(t_philo *philo, char *str, int stat)
{
    uint64_t    now;

    pthread_mutex_lock(&philo->arg->mutex_print);
    if (is_alive(philo->arg) || stat == DEAD)
    {
        now = get_curtime();
        printf("%7ld %3d %s\n", now - philo->thread_start_time, philo->id, str);
    }
    pthread_mutex_unlock(&philo->arg->mutex_print);
}

void    act_sleep(t_philo *philo)
{
    print_stat(philo, "is sleeping", SLEEP);
    pass_time(philo->arg->time_to_sleep, philo->arg);
    philo->rotate_count--;
}

void    act_eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->arg->fork[philo->left]);
    print_stat(philo, "has taken a fork", FORK);
    pthread_mutex_lock(&philo->arg->fork[philo->right]);
    print_stat(philo, "has taken a fork", FORK);
    {
        pthread_mutex_lock(&philo->mutex_last_eat);
        philo->last_eat_time = get_curtime();
        pthread_mutex_unlock(&philo->mutex_last_eat);
        print_stat(philo, "is eating", EAT);
        pass_time(philo->arg->time_to_eat, philo->arg);
        philo->rotate_count--;
        pthread_mutex_lock(&philo->mutex_eat_count);
        philo->eat_count++;
        pthread_mutex_unlock(&philo->mutex_eat_count);
    }
    pthread_mutex_unlock(&philo->arg->fork[philo->right]);
    pthread_mutex_unlock(&philo->arg->fork[philo->left]);
}
