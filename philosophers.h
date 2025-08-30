/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:25:47 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/08/30 19:01:58 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
//# include "libft/libft.h"

typedef struct s_conds
{
	pthread_mutex_t	*writing;
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
	int				*status;
	int				f;
	int				s;
	int				num;
	int				eat_count;
}	t_plato;

t_conds		*parser(t_conds *res, int argc, char **argv);
void		*aristotle(void *plato_ptr);
long long	my_time(struct timeval tmp);
long long	timedif(struct timeval t1, struct timeval t2);
void		ft_print(t_plato plato, int code);
void		ft_usleep(size_t milisec);

#endif