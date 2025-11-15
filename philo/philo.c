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

static void	start_dinner(t_plato *plato, t_conds *conds, pthread_mutex_t *mutex)
{
	int	i;

	i = -1;
	while (++i < conds->n)
	{
		if (pthread_create(&plato[i].id, NULL, aristotle, &(plato[i])))
		{
			*conds->status = 0;
			break ;
		}
	}
	check_death(*conds, plato);
	i = 0;
	while (i < conds->n)
		pthread_join(plato[i++].id, NULL);
	destroy_mutex_arr(mutex, conds->n);
	destroy_conds_mutex(conds, 3);
	free(plato);
}

int	main(int argc, char **argv)
{
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
	gettimeofday(&conds->starttime, NULL);
	plato = get_platos(conds, mutex);
	if (!plato)
		return (destroy_mutex_arr(mutex, conds->n), 0);
	start_dinner(plato, conds, mutex);
	return (0);
}
