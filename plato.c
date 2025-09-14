#include "philo.h"

pthread_mutex_t	*get_forks(t_conds *conds)
{
	pthread_mutex_t	*mutex;
	int				i;

	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * conds->n);
	if (!mutex)
		return (free_conds(conds), NULL);
	i = 0;
	while (i < conds->n)
	{
		if (pthread_mutex_init(&(mutex[i]), NULL))
			return (destroy_mutex_arr(mutex, i), free_conds(conds), NULL);
		i++;
	}
	return (mutex);
}


static void	fill_plato(t_plato *plato, pthread_mutex_t *mutex, int i)
{
	t_conds	*conds;

	conds = plato->conds_ptr;
	plato[i].last_eat = conds->starttime;
	plato[i].num = i;
	if (i % 2)
	{
		gettimeofday(&conds->starttime, NULL);
		plato[i].first = &mutex[i];
		plato[i].second = &mutex[0];
		if (i + 1 < conds->n)
			plato[i].second = &mutex[i + 1];
	}
	else
	{
		plato[i].second = &mutex[i];
		plato[i].first = &mutex[0];
		if (i + 1 < conds->n)
			plato[i].first = &mutex[i + 1];
	}
	plato[i].eat_count = 0;
}

t_plato	*get_platos(t_conds *conds, pthread_mutex_t *mutex)
{
	t_plato	*plato;
	int		i;

	plato = (t_plato *)malloc(sizeof(t_plato) * conds->n);
	if (!plato)
		return (destroy_conds_mutex(conds, 3), NULL);
	i = 0;
	while (i < conds->n)
	{
		plato[i].conds_ptr = conds;
		fill_plato(plato, mutex, i++);
	}
	return (plato);
}
