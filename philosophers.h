#ifndef	PHILOSOPHERS_H
# define	PHILOSOPHERS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
//# include "libft/libft.h"

typedef struct s_conds
{
	pthread_mutex_t	*p;
	int	n;
	int	eat;
	int	sleep;
	int	die;
	int	fin;
} t_conds;

typedef	struct s_plato
{
	pthread_mutex_t	*writing;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	int	*status;
	int	num;
	int	eat;
	int	sleep;
	int	die;
	int	fin;
} t_plato;


t_conds	*parser(int argc, char **argv);

#endif