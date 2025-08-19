#ifndef	PHILOSOPHERS_H
# define	PHILOSOPHERS_H

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
	int	n;
	int	eat;
	int	sleep;
	int	die;
	int	fin;
} t_conds;

typedef	struct s_plato
{
	t_conds			*conds_cpy;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	struct timeval	last_eat;
	int				*status;
	int				f;
	int				s;
	int				num;
} t_plato;

t_conds	*parser(int argc, char **argv);

#endif