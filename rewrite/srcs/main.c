/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 06:08:44 by jischoi           #+#    #+#             */
/*   Updated: 2023/02/07 06:10:35 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool  check_input(int argc, char **argv)
{
    int i;

    i = 0;
    if (argc < 5 || argc > 6)
        return (FALSE);
    while (++i < argc)
    {
        if (ft_atoi(argv[i]) == '-' || ft_atoi(argv[i]) <= 0)
            return (FALSE);
    }
    return (TRUE);
}

int main(int argc, char **argv)
{
    t_arg   arg;
    int     i;

    if (check_input(argc, argv))
    {
        init_arg(&arg, argc, argv);
        i = 0;
        while (i < arg.philo_num)
        {
            pthread_create(&arg.philo[i].thread, NULL, &routine, (void *)&arg.philo[i]);
            i++;
        }
        monitor(&arg);
        destroy_free(&arg);
    }
    else
        printf(CYAN"USAGE > ./philo [number_of_philosophers] [time_to_die]" \
                "[time_to_eat] [time_to_sleep] [num_each_philos_eat(optional)]\n"RESET);
    return (EXIT_SUCCESS);
}