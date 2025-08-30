/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:27:53 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/08/30 19:23:19 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	my_time(struct timeval tmp)
{
	long long	res;

	res = tmp.tv_sec * 1000 + tmp.tv_usec / 1000;
	return (res);
}

long long	timedif(struct timeval t1, struct timeval t2)
{
	return (my_time(t1) - my_time(t2));
}

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

void	ft_print(t_plato plato, int code)
{
	struct timeval	tmp;

	pthread_mutex_lock(plato.conds_ptr->writing);
	if (*plato.status)
	{
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
		{
			write(1, " died\n", 7);
			*plato.status = 0;
		}
	}
	pthread_mutex_unlock(plato.conds_ptr->writing);
}
