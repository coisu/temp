/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 06:08:46 by jischoi           #+#    #+#             */
/*   Updated: 2023/02/07 07:35:49 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void    ending_finish_meal(t_arg *arg)
// {
//     pthread_mutex_lock(&arg->mutex_alive);
//     arg->alive = FALSE;
//     pthread_mutex_unlock(&arg->mutex_alive);
//     printf("Every Philosophers finished their meal.\n");
// }

// void    ending_dead(t_arg *arg, int i)
// {
//     pthread_mutex_lock(&arg->mutex_alive);
//     arg->alive = FALSE;
//     pthread_mutex_unlock(&arg->mutex_alive);
//     // print_stat(&arg->philo[i], "died", DEAD);
// }

void	exit_threads(t_arg *arg)
{
	pthread_mutex_lock(&arg->mutex_alive);
	arg->alive = FALSE;
	pthread_mutex_unlock(&arg->mutex_alive);
}

void	die(t_arg *arg, int i)
{
	exit_threads(arg);
	print_stat(&arg->philo[i], "died",DEAD);
}

static int  check_eat_count(t_arg *arg, int finish_eat, int i)
{
    pthread_mutex_lock(&arg->philo[i].mutex_eat_count);
    if (arg->must_eat != -1 && arg->philo[i].eat_count >= arg->must_eat)
        finish_eat++;
    pthread_mutex_unlock(&arg->philo[i].mutex_eat_count);
    return (finish_eat);
}

int monitor(t_arg *arg)
{
    int i;
    int finish_eat;

    while (1)
    {
        i = 0;
        finish_eat = 0;
        if (arg->philo_num == 1)
        {
            pass_time(arg->time_to_die, arg);
            return (die(arg, 0), 1);
        }
        while (i < arg->philo_num)
        {
            if (is_dead(arg, i))
                return (die(arg, i), 1);
            finish_eat = check_eat_count(arg, finish_eat, i);
            if (finish_eat == arg->philo_num)
                return (exit_threads(arg), 1);
            i++;
        }
        usleep(1);
    }
    return (0);
}