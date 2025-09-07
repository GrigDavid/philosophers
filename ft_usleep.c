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
			break;
		}
		pthread_mutex_unlock(conds->status_check);
		usleep(500);
	}
}