/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:19:13 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/09/15 15:52:01 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_putlong(long long num)
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

static void	die(t_conds *conds)
{
	write(1, " is thinking\n", 13);
	pthread_mutex_lock(conds->status_check);
	*conds->status = 0;
	pthread_mutex_unlock(conds->status_check);
}


void	print_message(t_plato plato, int code)
{
	struct timeval	tmp;

	pthread_mutex_lock(plato.conds_ptr->writing);
	pthread_mutex_lock(plato.conds_ptr->status_check);
	if (*plato.conds_ptr->status)
	{
		pthread_mutex_unlock(plato.conds_ptr->status_check);
		gettimeofday(&tmp, NULL);
		ft_putlong(timedif(tmp, plato.conds_ptr->starttime));
		write(1, " ", 1);
		ft_putlong(plato.num + 1);
		if (code == 1)
			write(1, " has taken a fork\n", 18);
		else if (code == 2)
			write(1, " is eating\n", 11);
		else if (code == 3)
			write(1, " is sleeping\n", 13);
		else if (code == 4)
			write(1, " is thinking\n", 13);
		else
			die(plato.conds_ptr);
	}
	else
		pthread_mutex_unlock(plato.conds_ptr->status_check);
	pthread_mutex_unlock(plato.conds_ptr->writing);
}
