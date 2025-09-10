/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:19:50 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/09/10 17:20:02 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_cur_time(void)
{
	struct timeval	currtime;

	if (gettimeofday(&currtime, NULL) == -1)
	{
		printf("get time error\n");
		return (0);
	}
	return (currtime.tv_sec * 1000 + currtime.tv_usec / 1000);
}

void	ft_usleep(size_t milisec, t_conds *conds)
{
	size_t	start;

	start = get_cur_time();
	while (milisec > get_cur_time() - start)
	{
		pthread_mutex_lock(conds->status_check);
		if (!*conds->status)
		{
			pthread_mutex_unlock(conds->status_check);
			return ;
		}
		pthread_mutex_unlock(conds->status_check);
		usleep(500);
	}
}
