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

void	destroy_mutex_arr(pthread_mutex_t *mutex, int i)
{
	int	j;

	j = 0;
	while (j < i)
		pthread_mutex_destroy(&mutex[j++]);
	free(mutex);
}

t_conds	*get_conds(int argc, char **argv)
{
	t_conds	*conds;

	conds = parser(argc, argv);
	if (!conds)
		return (NULL);
	conds->writing = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!conds->writing)
		return (NULL);
	conds->last_eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!conds->last_eat)
		return (free(conds->writing), NULL);
	conds->status_check = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!conds->status_check)
		return (free(conds->writing), free(conds->last_eat), NULL);
	conds->status = (int *)malloc(sizeof(int));
	if (!conds->status)
	{
		free(conds->writing);
		return (free(conds->last_eat), free(conds->status_check), NULL);
	}
	*conds->status = 1;
	gettimeofday(&conds->starttime, NULL);
	return (conds);
}

void	free_conds(t_conds *conds)
{
	free(conds->writing);
	free(conds->last_eat);
	free(conds->status_check);
	free(conds->status);
	free(conds);
}

pthread_mutex_t	*get_forks(t_conds *conds)
{
	pthread_mutex_t	*mutex;
	int				i;

	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * conds->n);
	if (!mutex)
		return (free_conds(conds), NULL);
	i = 0;
	while (i < conds->n)
	{
		if (pthread_mutex_init(&(mutex[i]), NULL))
			return (destroy_mutex_arr(mutex, i), free_conds(conds), NULL);
		i++;
	}
	return (mutex);
}

void	destroy_conds_mutex(t_conds *conds, int n)
{
	if (n >= 1)
		pthread_mutex_destroy(conds->writing);
	if (n >= 2)
		pthread_mutex_destroy(conds->last_eat);
	if (n == 3)
		pthread_mutex_destroy(conds->status_check);
	free_conds(conds);
}

int	init_cond_mutexes(t_conds *conds)
{
	if (pthread_mutex_init(conds->writing, NULL))
		return (free_conds(conds), 0);
	if (pthread_mutex_init(conds->last_eat, NULL))
		return (destroy_conds_mutex(conds, 1), 0);
	if (pthread_mutex_init(conds->status_check, NULL))
		return (destroy_conds_mutex(conds, 2), 0);
	return (1);
}

t_plato	*get_platos(t_conds *conds, pthread_mutex_t *mutex)
{
	t_plato	*plato;
	int		i;

	plato = (t_plato *)malloc(sizeof(t_plato) * conds->n);
	if (!plato)
		return (destroy_conds_mutex(conds, 3), NULL);
	i = 0;
	while (i < conds->n)
	{
		plato[i].last_eat = conds->starttime;
		plato[i].conds_ptr = conds;
		plato[i].num = i;
		if (i % 2)
		{
			plato[i].first = &mutex[i];
			plato[i].second = &mutex[0];
			if (i + 1 < conds->n)
				plato[i].second = &mutex[i + 1];
		}
		else//
		{//
			plato[i].second = &mutex[i];
			plato[i].first = &mutex[0];
			if (i + 1 < conds->n)
				plato[i].first = &mutex[i + 1];
		}//
		plato[i++].eat_count = 0;
	}
	return (plato);
}

int	main(int argc, char **argv)
{
	int				i;
	t_plato			*plato;
	t_conds			*conds;
	pthread_mutex_t	*mutex;

	conds = get_conds(argc, argv);
	if (!conds)
		return (0);
	mutex = get_forks(conds);
	if (!mutex)
		return (0);
	if (!init_cond_mutexes(conds))
		return (destroy_mutex_arr(mutex, conds->n), 0);
	plato = get_platos(conds, mutex);
	if (!plato)
		return (destroy_mutex_arr(mutex, conds->n), 0);
	i = -1;
	while (++i < conds->n)
		pthread_create(&plato[i].id, NULL, aristotle, &(plato[i]));
	check_death(*conds, plato);
	i = 0;
	while (i < conds->n)
		pthread_join(plato[i++].id, NULL);
	destroy_mutex_arr(mutex, conds->n);
	destroy_conds_mutex(conds, 3);
	free(plato);
	return (0);
}
