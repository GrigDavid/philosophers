/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aristotle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:27:38 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/09/11 15:57:26 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_plato *plato, t_conds *conds)
{
	pthread_mutex_lock(plato->first);
	print_message(*plato, 1);
	if (conds->n > 1)
	{
		pthread_mutex_lock(plato->second);
		print_message(*plato, 1);
		print_message(*plato, 2);
		pthread_mutex_lock(conds->last_eat);
		gettimeofday(&(plato->last_eat), NULL);
		pthread_mutex_unlock(conds->last_eat);
		ft_usleep(conds->eat, conds);
		pthread_mutex_lock(conds->last_eat);
		if (plato->eat_count < conds->fin)
			plato->eat_count++;
		pthread_mutex_unlock(conds->last_eat);
		pthread_mutex_unlock(plato->second);
	}
	else
	{
		ft_usleep(conds->die + 1, conds);//problemi bun
	}
	pthread_mutex_unlock(plato->first);
}

static void	ph_sleep(t_plato *plato, t_conds *conds)
{
	print_message(*plato, 3);
	pthread_mutex_lock(conds->status_check);
	if (*conds->status)
	{
		pthread_mutex_unlock(conds->status_check);
		ft_usleep(conds->sleep, conds);
		print_message(*plato, 4);
		//ft_usleep ((conds->die - conds->eat - conds->sleep), conds);
	}
	else
		pthread_mutex_unlock(conds->status_check);
}

void	*aristotle(void *plato_ptr)
{
	t_conds	*conds;
	t_plato	*plato;

	plato = (t_plato *)plato_ptr;
	conds = plato->conds_ptr;
	print_message(*plato, 4);
	if (plato->num % 2 == 0)
		usleep(500);
	pthread_mutex_lock(conds->status_check);
	while (*conds->status)
	{
		pthread_mutex_unlock(conds->status_check);
		eat(plato, conds);
		ph_sleep(plato, conds);
		pthread_mutex_lock(conds->status_check);
	}
	pthread_mutex_unlock(conds->status_check);
	return (NULL);
}
