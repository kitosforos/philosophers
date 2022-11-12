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
	if ((p->id - 1) % 2 != 0)
		usleep(10);
	while (1 && p->var->stop == 0)
	{
		pthread_mutex_lock(&p->var->mut[p->id - 1]);
		printf("%ldms %d has taken a fork\n", program_time(p->var), p->id);
		pthread_mutex_lock(&p->var->mut[p->id % (p->var->pnum)]);
		printf("%ldms %d has taken a fork\n", program_time(p->var), (p->id));
		printf("%ldms %d is eating\n", program_time(p->var), p->id);
		usleep(p->var->time_eat * 1000);
		p->last_meal = my_time();
		p->total_ate++;
		usleep(1);
		pthread_mutex_unlock(&p->var->mut[p->id - 1]);
		pthread_mutex_unlock(&p->var->mut[p->id % (p->var->pnum)]);
		printf("%ldms %d is sleeping\n", program_time(p->var), (p->id));
		usleep(p->var->time_sleep * 1000);
		printf("%ldms %d is thinking\n", program_time(p->var), p->id);
	}
	return (NULL);
}

void	read_args(t_data *pr, char *argv[])
{
	pr->p = malloc(sizeof(t_program));
	if (!pr->p)
		return ;
	pr->p->pnum = ft_atoi(argv[1]);
	pr->p->time_die = ft_atoi(argv[2]);
	pr->p->time_eat = ft_atoi(argv[3]);
	pr->p->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		pr->p->max_eat = ft_atoi(argv[5]);
	pr->p->time = my_time();
	pr->p->ph_eated = 0;
	pr->p->stop = 0;
}

int	my_init(t_data *pr)
{
	int	i;

	i = 0;
	pr->ph = malloc(sizeof(t_philo) * (pr->p->pnum));
	if (!pr->ph)
		return (1);
	pr->p->mut = malloc(sizeof(pthread_mutex_t) * (pr->p->pnum));
	if (!pr->p->mut)
		return (1);
	while (i < pr->p->pnum)
		pthread_mutex_init(&pr->p->mut[i++], NULL);
	i = 0;
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
	int		ret;

	if (argc < 5 || argc >= 7)
		return (my_exit());
	ret = 0;
	pr = malloc(sizeof(t_data));
	if (!pr)
		return (my_exit());
	ret = check_args(argv);
	if (ret)
	{
		free(pr);
		return (my_exit());
	}
	read_args(pr, argv);
	my_init(pr);
	my_end(pr, argv);
	my_free(pr);
	free(pr);
	return (0);
}
