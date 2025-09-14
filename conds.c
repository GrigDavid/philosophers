#include "philo.h"

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
