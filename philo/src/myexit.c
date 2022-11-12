#include "philo.h"

int	my_exit(void)
{
	ft_putstr_fd("Error.\n", 2);
	return (1);
}

int	my_exit_and_free(t_data	*pr)
{
	free(pr);
	return (my_exit());
}

void	my_free(t_data *pr)
{
	int	i;

	i = 0;
	pr->p->stop = 1;
	while (i < pr->p->pnum)
	{
		pthread_join(pr->ph[i].t, NULL);
		pthread_mutex_destroy(&pr->p->mut[i++]);
	}
	free(pr->p->mut);
	free(pr->p);
	free(pr->ph);
}
