/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aristotle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:27:38 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/08/30 19:27:55 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_plato *plato, t_conds *conds)
{
	pthread_mutex_lock(plato->first);
	ft_print(*plato, 1);
	if (conds->n > 1)
	{
		pthread_mutex_lock(plato->second);
		ft_print(*plato, 1);
		ft_print(*plato, 2);
		pthread_mutex_lock(conds->writing);
		gettimeofday(&(plato->last_eat), NULL);
		pthread_mutex_unlock(conds->writing);
		ft_usleep(conds->eat);
		pthread_mutex_lock(conds->writing);
		plato->eat_count++;
		pthread_mutex_unlock(conds->writing);
		ft_print(*plato, 3);
		pthread_mutex_unlock(plato->second);
	}
	else
		ft_usleep(conds->die + 1);
	pthread_mutex_unlock(plato->first);
}

void	ph_sleep(t_plato *plato, t_conds *conds)
{
	pthread_mutex_lock(conds->writing);
	if (*plato->status)
	{
		pthread_mutex_unlock(conds->writing);
		ft_usleep(conds->sleep);
		ft_print(*plato, 4);
	}
	else
		pthread_mutex_unlock(conds->writing);
}

void	*aristotle(void *plato_ptr)
{
	t_conds	*conds;
	t_plato	*plato;
	int		i;

	i = 0;
	plato = (t_plato *)plato_ptr;
	conds = plato->conds_ptr;
	ft_print(*plato, 4);
	if (plato->num % 2 == 0)
		ft_usleep((conds->eat / 2));
	pthread_mutex_lock(conds->writing);
	while (*plato->status)
	{
		pthread_mutex_unlock(conds->writing);
		eat(plato, conds);
		ph_sleep(plato, conds);
		pthread_mutex_lock(conds->writing);
	}
	pthread_mutex_unlock(conds->writing);
	return (NULL);
}
