#include "philo.h"

void	my_end(t_data *pr, char *argv[])
{
	int	i;

	i = 0;
	while (1)
	{
		if (my_time() - pr->ph[i].last_meal > pr->p->time_die)
		{
			printf("%ldms %d died\n", program_time(pr->p), pr->ph[i].id);
			return ;
		}
		if (pr->ph[i].total_ate >= pr->p->max_eat && argv[5]
			&& pr->ph[i].eated == 0)
		{
			pr->ph[i].eated = 1;
			pr->p->ph_eated++;
		}
		if (pr->p->ph_eated == pr->p->pnum)
			return ;
		i = (i + 1) % pr->p->pnum;
	}
}

void	*prueba(void *ph)
{
	t_philo	*p;

	p = (t_philo *)ph;
	while (1 && p->var->stop == 0)
	{
		pthread_mutex_lock(&p->var->mut[p->id - 1]);
		if (p->var->stop == 1)
			break ;
		printf("%ldms %d has taken a fork\n", program_time(p->var), p->id);
		if (p->var->pnum == 1)
			break ;
		pthread_mutex_lock(&p->var->mut[p->id % (p->var->pnum)]);
		if (p->var->stop == 1)
			break ;
		prueba2(p);
		if (p->var->stop == 1)
			break ;
		printf("%ldms %d is sleeping\n", program_time(p->var), (p->id));
		usleep(p->var->time_sleep * 1000);
		if (p->var->stop == 1)
			break ;
		printf("%ldms %d is thinking\n", program_time(p->var), p->id);
	}
	return (NULL);
}

int	read_args(t_data *pr, char *argv[])
{
	pr->p = malloc(sizeof(t_program));
	if (!pr->p)
		return (1);
	pr->p->pnum = ft_atoi(argv[1]);
	pr->p->time_die = ft_atoi(argv[2]);
	pr->p->time_eat = ft_atoi(argv[3]);
	pr->p->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		pr->p->max_eat = ft_atoi(argv[5]);
	pr->p->time = my_time();
	pr->p->ph_eated = 0;
	pr->p->stop = 0;
	return (0);
}

int	my_init(t_data *pr)
{
	int	i;

	i = 0;
	pr->ph = malloc(sizeof(t_philo) * (pr->p->pnum));
	if (!pr->ph)
		return (1);
	if (my_mutex_init(pr))
		return (1);
	while (i < pr->p->pnum)
	{
		pr->ph[i].id = i + 1;
		pr->ph[i].var = pr->p;
		pr->ph[i].last_meal = my_time();
		pr->ph[i].total_ate = 0;
		pr->ph[i].eated = 0;
		pthread_create(&pr->ph[i].t, NULL, &prueba, &pr->ph[i]);
		usleep(100);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	*pr;

	if (argc < 5 || argc >= 7)
		return (my_exit());
	pr = malloc(sizeof(t_data));
	if (!pr)
		return (my_exit());
	if (check_args(argv))
		return (my_exit_and_free(pr));
	if (read_args(pr, argv))
		return (my_exit_and_free(pr));
	if (my_init(pr))
		return (my_exit_and_free(pr));
	my_end(pr, argv);
	my_free(pr);
	free(pr);
	return (0);
}
