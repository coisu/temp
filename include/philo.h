
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>

# define TO_MSEC		1000

# define PEAT_INF		-1

# define THINK			0
# define FORKS			1
# define EAT			2
# define SLEEP			3
# define DEAD			4

# define FILL			0
# define FULL			1

# define FALSE			0
# define TRUE			1

# define PTH_SUCCESS	0
# define EXIT_PASS		-1

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define BLUE		"\x1b[34m"
# define YELLOW		"\x1b[33m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"

# define RESET		"\x1b[0m"

struct	s_info;

typedef struct s_philo
{
    struct s_arg	*arg;
	int				num;
	int				stat;
	int				starve;
	int				eat_count;
	uint64_t		last_num_must_eat;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
    pthread_t       thread;
}					t_philo;

typedef struct s_arg
{
	int				philo_num;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				num_must_eat;
	uint64_t		start_time;
	int				finished_eat;
    int             finish;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
}					t_arg;

/* UTILS */
int	ft_atoi(const char *str);
uint64_t	ft_get_time(void);

/* ACT */
int	ft_philo_action(t_arg *arg, t_philo *philo);
int	ft_philo_printf(t_arg *arg, int num, char *msg);
void	ft_pass_time(uint64_t  wait_time, t_arg *arg);

/* THREAD */
int	ft_philo_start(t_arg *arg, t_philo *philo);

/* INIT */
int	ft_arg_init(t_arg *arg, int argc, char *argv[]);
int	ft_philo_init(t_philo **philo, t_arg *arg);

/* MAIN */
int	main(int argc, char *argv[]);

#endif