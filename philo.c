/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:36:17 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/09/07 13:36:44 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex_array(pthread_mutex_t *mutex, int i)
{
	int	j;

	j = 0;
	while (j < i)
		pthread_mutex_destroy(&mutex[j++]);
}

int	main(int argc, char **argv)
{
	int				i;
	t_plato			*plato;
	t_conds			conds;
	pthread_mutex_t	*mutex;
	int				status;

	if (!parser(&conds, argc, argv))
		return (0);
	status = 1;
	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * conds.n);
	if (!mutex)
		return (0);
	conds.writing = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!conds.writing)
		return (free(mutex), 1);
	conds.last_eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!conds.last_eat)
		return (free(mutex), 1);
	conds.status_check = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!conds.status_check)
		return (free(mutex), 1);
	i = -1;
	while (++i < conds.n)
	{
		if (pthread_mutex_init(&(mutex[i]), NULL))
			return (destroy_mutex_array(mutex, i), free(mutex), free(conds.writing), 0); // FIRE IN THE HALL
	}
	if (pthread_mutex_init(conds.writing, NULL))
		return (destroy_mutex_array(mutex, i), free(mutex), free(conds.writing), 0);
	if (pthread_mutex_init(conds.last_eat, NULL))
		return (destroy_mutex_array(mutex, i), free(mutex), free(conds.writing), 0);
	if (pthread_mutex_init(conds.status_check, NULL))
		return (destroy_mutex_array(mutex, i), free(mutex), free(conds.writing), 0);
	plato = (t_plato *)malloc(sizeof(t_plato) * conds.n);
	if (!plato)
		return (destroy_mutex_array(mutex, i), free(mutex), free(conds.writing), 0);
	gettimeofday(&conds.starttime, NULL);
	i = 0;
	conds.status = &status;
	while (i < conds.n)
	{
		plato[i].last_eat = conds.starttime;
		plato[i].conds_ptr = &conds;
		plato[i].num = i;
		if (i % 2)
		{
			plato[i].f = i;
			plato[i].s = i + 1;
			if (i >= conds.n - 1)
				plato[i].s = 0;
		}
		else
		{
			plato[i].f = i + 1;
			plato[i].s = i;
			if (i >= conds.n - 1)
				plato[i].f = 0;
		}
		plato[i].first = &(mutex[plato[i].f]);
		plato[i].second = &(mutex[plato[i].s]);
		i++;
	}
	i = -1;
	while (++i < conds.n)
		pthread_create(&plato[i].id, NULL, aristotle, &(plato[i]));
	check_death(conds, plato);
	i = 0;
	while (i < conds.n)
		pthread_join(plato[i++].id, NULL);
	i = 0;
	while (i < conds.n)
		pthread_mutex_destroy(&mutex[i++]);
	free(conds.writing);
	free(mutex);
	free(plato);
	return (0);
}
