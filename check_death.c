/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:20:25 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/09/10 17:20:40 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	checking(t_conds conds, t_plato *plato, struct timeval	tmp, int *eaten)
{
	int	i;

	i = -1;
	while (++i < conds.n)
	{
		pthread_mutex_lock(conds.last_eat);
		if (conds.fin >= 0 && plato[i].eat_count >= conds.fin)
			(*eaten)++;
		pthread_mutex_unlock(conds.last_eat);
		pthread_mutex_lock(conds.last_eat);
		gettimeofday(&tmp, NULL);
		if (timedif(tmp, plato[i].last_eat) > conds.die)
		{
			pthread_mutex_unlock(conds.last_eat);
			print_message(plato[i], 5);
			pthread_mutex_lock(conds.status_check);
			*conds.status = 0;
			return (pthread_mutex_unlock(conds.status_check), 0);
		}
		else
			pthread_mutex_unlock(conds.last_eat);
	}
	return (1);
}

void	check_death(t_conds conds, t_plato *plato)
{
	int				eaten;
	struct timeval	tmp;

	pthread_mutex_lock(conds.status_check);
	while (*conds.status)
	{
		eaten = 0;
		pthread_mutex_unlock(conds.status_check);
		if (!checking(conds, plato, tmp, &eaten))
			return ;
		ft_usleep(4, &conds);
		pthread_mutex_lock(conds.status_check);
		if (eaten == conds.n)
			*conds.status = 0;
	}
	pthread_mutex_unlock(conds.status_check);
}
