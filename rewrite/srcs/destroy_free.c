/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 06:08:39 by jischoi           #+#    #+#             */
/*   Updated: 2023/02/07 06:25:08 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    destroy_free(t_arg *arg)
{
    int i;

    i = -1;
    while (++i < arg->philo_num)
        pthread_join(arg->philo[i].thread, NULL);
    i = 0;
    while (i < arg->philo_num)
    {
        pthread_mutex_destroy(&arg->fork[i]);
        pthread_mutex_destroy(&arg->philo[i].mutex_last_eat);
        pthread_mutex_destroy(&arg->philo[i].mutex_eat_count);
        i++;
    }
    pthread_mutex_destroy(&arg->mutex_alive);
    pthread_mutex_destroy(&arg->mutex_print);
    free(arg->fork);
    free(arg->philo);
}