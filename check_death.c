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

void	check_death(t_conds conds, t_plato *plato)
{
	int				i;
	int				eaten;
	struct timeval	tmp;

	pthread_mutex_lock(conds.status_check);
	while (*conds.status)
	{
		pthread_mutex_unlock(conds.status_check);
		eaten = 0;
		i = 0;
		while (i < conds.n)
		{
			pthread_mutex_lock(conds.last_eat);
			if (conds.fin >= 0 && plato[i].eat_count >= conds.fin)
				eaten++;
			pthread_mutex_unlock(conds.last_eat);
			pthread_mutex_lock(conds.last_eat);
			gettimeofday(&tmp, NULL);//karam krchatem
			if (timedif(tmp, plato[i].last_eat) > (long long)conds.die)
			{
				pthread_mutex_unlock(conds.last_eat);
				print_message(plato[i], 5);
				pthread_mutex_lock(conds.status_check);
				*conds.status = 0;
				return (pthread_mutex_unlock(conds.status_check), (void)0);
			}
			else
				pthread_mutex_unlock(conds.last_eat);
			i++;
		}
		ft_usleep(2, &conds);
		pthread_mutex_lock(conds.status_check);
		if (eaten == conds.n)
			*conds.status = 0;
	}
	pthread_mutex_unlock(conds.status_check);
}
