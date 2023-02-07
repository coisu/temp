
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>

# define PEAT_INF		-1

# define FALSE			0
# define TRUE			1

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define BLUE		"\x1b[34m"
# define YELLOW		"\x1b[33m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

typedef struct  timeval t_timeval;
typedef int             t_bool;

typedef enum act {
    FORK,
    EAT,
    SLEEP,
    THINK, 
    DEAD
}   t_act;

typedef struct s_philo
{
    struct s_arg	*arg;
	int				id;
	int				eat_count;
    int             rotate_count;
    int				right;
	int				left;
    uint64_t        thread_start_time;
	uint64_t		last_eat_time;
    pthread_mutex_t mutex_last_eat;
    pthread_mutex_t mutex_eat_count;
    pthread_t       thread;
}					t_philo;

typedef struct s_arg
{
	int				philo_num;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				must_eat;
    t_bool          alive;
    pthread_mutex_t mutex_alive;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*fork;
    t_philo         *philo;
}					t_arg;

/* UTILS */
int	        ft_atoi(const char *nptr);
void	    pass_time(uint64_t wait, t_arg *arg);
uint64_t	get_curtime(void);
t_bool	    is_alive(t_arg *arg);
t_bool      is_dead(t_arg *arg, int i);

/* DESTROY & FREE */
void    destroy_free(t_arg *arg);

/* MONITOR */
int monitor(t_arg *arg);

/* ACT */
void        act_eat(t_philo *philo);
void        act_sleep(t_philo *philo);
void        print_stat(t_philo *philo, char *str, int stat);

/* ROUTINE */
void    *routine(void *content);

/* INIT */
void    init_arg(t_arg *arg, int argc, char **argv);

/* MAIN */
int	main(int argc, char **argv);

#endif