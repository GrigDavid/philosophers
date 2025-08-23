/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:36:17 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/08/23 18:20:17 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/wait.h>

void	*aristotle(void *plato_cpy)
{
	t_conds	*conds;
	t_plato	*plato;
	int		i;

	i = 0;
	plato = (t_plato *)plato_cpy;
	conds = plato->conds_cpy;
	pthread_mutex_lock(conds->writing);
	while (*plato->status)
	{
		pthread_mutex_unlock(conds->writing);
		ft_print(*plato, 4);//think
		pthread_mutex_lock(plato->first);
		ft_print(*plato, 1);//fork
		pthread_mutex_lock(plato->second);
		ft_print(*plato, 1);//fork
		ft_print(*plato, 2);//eating
		pthread_mutex_lock(conds->writing);
		gettimeofday(&(plato->last_eat), NULL);
		pthread_mutex_unlock(conds->writing);
		usleep(conds->eat * 1000);
		ft_print(*plato, 3);//sleep
		pthread_mutex_unlock(plato->second);
		pthread_mutex_unlock(plato->first);
		usleep(conds->sleep * 1000);
		pthread_mutex_lock(conds->writing);
	}
	pthread_mutex_unlock(conds->writing);
	write(1, "return el em arel, inch es uzum?\n", 34);
	return (NULL);
}


void	check_death(t_conds conds, t_plato *plato)
{
	int				i;
	struct timeval	tmp;

	pthread_mutex_lock(conds.writing);
	while (*plato[0].status)
	{
		pthread_mutex_unlock(conds.writing);
		i = 0;
		while (i < conds.n)
		{
			pthread_mutex_lock(conds.writing);
			gettimeofday(&tmp, NULL);
			if (timedif(tmp, plato[i].last_eat) >= (long long)conds.die)
			{
				pthread_mutex_unlock(conds.writing);
				ft_print(plato[i], 5);//death
			}
			else
				pthread_mutex_unlock(conds.writing);
			i++;
		}
		usleep(500);
		pthread_mutex_lock(conds.writing);
	}
	pthread_mutex_unlock(conds.writing);
}

int main(int argc, char **argv)
{ // LIBFT IS ***NOT*** ALLOWED
	int i;
	t_plato	*plato;
	t_conds	conds;
	pthread_mutex_t *mutex;
	int status;

	parser(&conds, argc, argv);
	status = 1;
	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * conds.n);
	if (!mutex)
		return (0);
	i = 0;
	while (i < conds.n)
	{
		pthread_mutex_init(&(mutex[i]), NULL); // check for fail
		i++;
	}
	pthread_mutex_init(conds.writing, NULL); //and possibly here
	plato = (t_plato *)malloc(sizeof(t_plato) * conds.n);
	if (!plato)
		return (free(mutex), 0);
	gettimeofday(&conds.starttime, NULL);
	i = 0;
	while (i < conds.n)
	{
		plato[i].last_eat = conds.starttime;
		plato[i].conds_cpy = &conds;
		plato[i].status = &status;
		plato[i].num = i;
		if (i % 2 == 0)
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
		// if (i % 2 == 1)
		// 	usleep(100);
		pthread_create(&plato[i].id, NULL, aristotle, &(plato[i]));
		i++;
	}
	check_death(conds, plato);
	i = 0;
	write(1, "ancanq\n", 7);
	printf("%d\n", conds.n);
	while (i < conds.n)
	{
		pthread_mutex_lock(conds.writing);
		write(1, "mta, harcer?\n", 14);

		pthread_mutex_unlock(conds.writing);
		pthread_join(plato[i++].id, NULL);
		write(1, "Som Ting Wong\n", 15);
	}
	free(mutex);
	free(plato);
	return (0);
}
