/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:36:17 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/08/30 19:30:15 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/wait.h>

size_t	get_cur_time(void)
{
	struct timeval	currtime;

	if (gettimeofday(&currtime, NULL) == -1)
	{
		printf("get time erreo\n");
		return (0);
	}
	return (currtime.tv_sec * 1000 + currtime.tv_usec / 1000);
}

void	ft_usleep(size_t milisec)
{
	size_t	start;

	start = get_cur_time();
	while (milisec > get_cur_time() - start)
		usleep(500);
}

void	check_death(t_conds conds, t_plato *plato)
{
	int				i;
	int				eaten;
	struct timeval	tmp;

	pthread_mutex_lock(conds.writing);
	while (*plato[0].status)
	{
		eaten = 0;
		i = 0;
		pthread_mutex_unlock(conds.writing);
		while (i < conds.n)
		{
			pthread_mutex_lock(conds.writing);
			if (conds.fin >= 0 && plato[i].eat_count >= conds.fin)
				eaten++;
			gettimeofday(&tmp, NULL);//karam krchatem
			if (timedif(tmp, plato[i++].last_eat) >= (long long)conds.die)
			{
				pthread_mutex_unlock(conds.writing);
				ft_print(plato[i - 1], 5);
				break ;
			}
			else
				pthread_mutex_unlock(conds.writing);
		}
		//pthread_mutex_unlock(conds.writing);//remove if going back
		ft_usleep(1);
		pthread_mutex_lock(conds.writing);
		if (eaten == conds.n)
			*plato[0].status = 0;
	}
	pthread_mutex_unlock(conds.writing);
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
	i = -1;
	while (++i < conds.n)
		pthread_mutex_init(&(mutex[i]), NULL); // check for fail
	pthread_mutex_init(conds.writing, NULL); //and possibly here
	plato = (t_plato *)malloc(sizeof(t_plato) * conds.n);
	if (!plato)
		return (free(mutex), free(conds.writing), 0);
	gettimeofday(&conds.starttime, NULL);
	i = 0;
	while (i < conds.n)
	{
		plato[i].last_eat = conds.starttime;
		plato[i].conds_ptr = &conds;
		plato[i].status = &status;
		plato[i].num = i;
		if (1)
		{
			plato[i].f = i;
			plato[i].s = i + 1;
			if (i >= conds.n - 1)
				plato[i].s = 0;
		}
		// else
		// {
		// 	plato[i].f = i + 1;
		// 	plato[i].s = i;
		// 	if (i >= conds.n - 1)
		// 		plato[i].f = 0;
		// }
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
	free(mutex);
	free(plato);
	return (0);
}
