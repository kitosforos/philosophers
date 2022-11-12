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
