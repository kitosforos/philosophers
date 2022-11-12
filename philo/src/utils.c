#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	signo;
	int	numero;

	i = 0;
	signo = 1;
	numero = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signo *= -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		numero = numero * 10 + (str[i] - '0');
		i++;
	}
	if (signo < 0)
		return (-1 * numero);
	else
		return (numero);
}

int	ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || !fd)
		return ;
	write(fd, s, ft_strlen(s));
}

int	is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != 0)
	{
		if ((arg[i] < '0' || arg[i] > '9'))
			return (1);
		i++;
	}
	return (0);
}
