/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:25:47 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/09/07 13:36:49 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>
# include <sys/wait.h>
//# include "libft/libft.h"

typedef struct s_conds
{
	pthread_mutex_t	*writing;
	pthread_mutex_t	*last_eat;
	pthread_mutex_t	*status_check;
	int				*status;
	struct timeval	starttime;
	int				n;
	int				eat;
	int				sleep;
	int				die;
	int				fin;
}	t_conds;

typedef struct s_plato
{
	t_conds			*conds_ptr;
	pthread_t		id;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	struct timeval	last_eat;
	int				f;
	int				s;
	int				num;
	int				eat_count;
}	t_plato;

void		*aristotle(void *plato_ptr);
void		check_death(t_conds conds, t_plato *plato);
void		ft_usleep(size_t milisec, t_conds *conds);
t_conds		*parser(int argc, char **argv);
void		print_message(t_plato plato, int code);
long long	my_time(struct timeval tmp);
long long	timedif(struct timeval t1, struct timeval t2);

#endif