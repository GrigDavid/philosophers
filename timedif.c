/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timedif.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:27:53 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/09/07 13:38:48 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	my_time(struct timeval tmp)
{
	long long	res;

	res = tmp.tv_sec * 1000 + tmp.tv_usec / 1000;
	return (res);
}

long long	timedif(struct timeval t1, struct timeval t2)
{
	return (my_time(t1) - my_time(t2));
}

