#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_program
{
	int				pnum;
	unsigned long	time_die;
	int				time_eat;
	int				time_sleep;
	int				max_eat;
	int				ph_eated;
	int				stop;
	unsigned long	time;
	pthread_mutex_t	*mut;
}	t_program;

typedef struct s_philo
{
	int				id;
	pthread_t		t;
	unsigned long	last_meal;
	int				total_ate;
	int				eated;
	t_program		*var;
}	t_philo;

typedef struct s_data
{
	t_philo		*ph;
	t_program	*p;
}	t_data;

//utils.c

int				ft_atoi(const char *str);
int				ft_strlen(char *str);
void			ft_putstr_fd(char *s, int fd);
int				is_number(char *arg);

//philo_utils.c

unsigned long	my_time(void);
unsigned long	program_time(t_program *pr);
int				check_args(char *argv[]);
void			my_free(t_data *pr);
int				my_mutex_init(t_data *pr);

//my_exit.c

int				my_exit(void);
int				my_exit_and_free(t_data	*pr);

#endif
