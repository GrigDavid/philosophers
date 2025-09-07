#include "philo.h"

int	ft_putlong(long long num)
{
	char	zero;

	zero = '0';
	if (num < 0)
	{
		write(1, "-", 1);
		return (ft_putlong(-1 * num));
	}
	if (num <= 9)
	{
		zero += num;
		return (write(1, &zero, 1));
	}
	zero += num % 10;
	ft_putlong(num / 10);
	return (write(1, &zero, 1));
}

void	print_message(t_plato plato, int code)
{
	struct timeval	tmp;

	pthread_mutex_lock(plato.conds_ptr->status_check);
	if (*plato.conds_ptr->status)
	{
		pthread_mutex_unlock(plato.conds_ptr->status_check);
		pthread_mutex_lock(plato.conds_ptr->writing);
		gettimeofday(&tmp, NULL);
		ft_putlong(timedif(tmp, plato.conds_ptr->starttime));
		write(1, " ", 1);
		ft_putlong(plato.num + 1);
		if (code == 1)
			write(1, " has taken a fork\n", 19);
		else if (code == 2)
			write(1, " is eating\n", 12);
		else if (code == 3)
			write(1, " is sleeping\n", 14);
		else if (code == 4)
			write(1, " is thinking\n", 14);
		else
			write(1, " died\n", 7);
		pthread_mutex_unlock(plato.conds_ptr->writing);
	}
	else
		pthread_mutex_lock(plato.conds_ptr->status_check);
}
