#include "philo.h"

unsigned long	my_time(void)
{
	struct timeval	time;
	unsigned long	l;
	unsigned long	s;
	unsigned long	u;

	gettimeofday(&time, NULL);
	s = (time.tv_sec * 1000);
	u = (time.tv_usec / 1000);
	l = s + u;
	return (l);
}

unsigned long	program_time(t_program *pr)
{
	return (my_time() - pr->time);
}

int	check_args(char *argv[])
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = is_number(argv[i]);
		if (j)
		{
			printf("\n%d", j);
			return (1);
		}
		i++;
	}
	return (0);
}

void	my_free(t_data *pr)
{
	int	i;

	i = 0;
	pr->p->stop = 1;
	while (i < pr->p->pnum)
	{
		pthread_mutex_destroy(&pr->p->mut[i]);
		pthread_join(pr->ph[i++].t, NULL);
	}
	free(pr->p->mut);
	free(pr->p);
	free(pr->ph);
	free(pr);
}

int	my_mutex_init(t_data *pr)
{
	int	i;

	i = 0;
	pr->p->mut = malloc(sizeof(pthread_mutex_t) * (pr->p->pnum));
	if (!pr->p->mut)
	{
		free(pr->ph);
		return (1);
	}
	while (i < pr->p->pnum)
		pthread_mutex_init(&pr->p->mut[i++], NULL);
	return (0);
}
