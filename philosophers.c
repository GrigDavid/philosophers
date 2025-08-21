#include "philosophers.h"
#include <sys/wait.h>

int	ft_putlong(long long num)
{
	char	zero;

	zero = '0';
	if (num < 0)
	{
		write(1, "-", 1);
		return (ft_putlong(-1 * num));
	}
	if (num <= 9)
	{
		zero += num;
		return (write(1, &zero, 1));
	}
	zero += num % 10;
	ft_putlong(num / 10);
	return (write(1, &zero, 1));
}

void	ft_print(long long time, t_plato plato, int code)//fork should not be printed
{
	if (*plato.status)
	{
		ft_putlong(time);
		write(1, " ", 1);
		ft_putlong(plato.num);
		if (code == 1)//fork
			write(1, " has taken a fork\n", 19);
		else if (code == 2)//eating
			write(1, " is eating\n", 12);
		else if (code == 3)//sleeping
			write(1, " is sleeping\n", 14);
		else if (code == 4)//thinking
			write(1, " is thinking\n", 14);
		else//died
			write(1, " died\n", 7);
	}
}


// skzbi hamar n = 5; eat = 100; sleep = 50; die = 200
/*
void	*aristotle(void *v_plato)
{
	t_plato	*plato;

	plato = (t_plato *)v_plato;
	ft_putstr_fd("before mutex: ",1);
	ft_putnbr_fd( plato->left, 1);
	ft_putchar_fd('\n', 1);
	pthread_mutex_lock(plato->mutex);
	usleep(1000000);
	ft_putstr_fd("inside mutex: ",1);
	ft_putnbr_fd( plato->left, 1);
	ft_putchar_fd('\n', 1);
	pthread_mutex_unlock(plato->mutex);
	return (NULL);

}*/

long long my_time(struct timeval tmp)
{
	long long res;

	res = tmp.tv_sec * 1000 + tmp.tv_usec / 1000;
	return (res);
}

long long timedif(struct timeval t1, struct timeval t2)
{
	return (my_time(t1) - my_time(t2));
}


void *aristotle(void *plato_cpy)
{
	struct timeval tmp;
	t_conds	*conds;
	t_plato *plato;
	int i;

	i = 0;
	plato = (t_plato *)plato_cpy;
	conds = plato->conds_cpy;
	while (*plato->status)
	{
		pthread_mutex_lock(plato->first);
		pthread_mutex_lock(conds->writing);
		gettimeofday(&tmp, NULL);
		if (*plato->status)
			ft_print(timedif(tmp, conds->starttime), *plato, 1);//printf("%lld : %d took fork %d with his left hand\n", timedif(tmp, conds->starttime), plato->num, plato->f);
		pthread_mutex_unlock(conds->writing);
		pthread_mutex_lock(plato->second);
		pthread_mutex_lock(conds->writing);
		gettimeofday(&tmp, NULL);
		if (*plato->status)
			ft_print(timedif(tmp, conds->starttime), *plato, 1);//printf("%lld: %d took fork %d with his right hand\n", timedif(tmp, conds->starttime), plato->num, plato->s);
		gettimeofday(&tmp, NULL);
		if (*plato->status)
			ft_print(timedif(tmp, conds->starttime), *plato, 2);//printf("%lld: philosopher %d is eating\n", timedif(tmp, conds->starttime), plato->num);
		pthread_mutex_unlock(conds->writing);
		usleep(conds->eat * 1000);
		gettimeofday(&(plato->last_eat), NULL);
		// i++;
		// if (conds->fin > 0 && i >= conds->fin)
		// 	*(plato->status) = 0;
		pthread_mutex_lock(conds->writing);
		gettimeofday(&tmp, NULL);
		if (*plato->status)
			ft_print(timedif(tmp, conds->starttime), *plato, 3);//printf("%lld : %d dropped forks %d and %d\n", timedif(tmp, conds->starttime), plato->num, plato->f, plato->s);
		pthread_mutex_unlock(conds->writing);
		pthread_mutex_unlock(plato->second);
		pthread_mutex_unlock(plato->first);
		usleep(conds->sleep * 1000);
		ft_print(timedif(tmp, conds->starttime), *plato, 4);//pthread_mutex_lock(conds->writing);
	}
	return (NULL);
}


int main(int argc, char **argv)
{ // LIBFT IS ***NOT*** ALLOWED
	int i;
	t_plato	*plato;
	t_conds	conds;
	pthread_mutex_t *mutex;
	pthread_mutex_t writing;
	int status;
	struct timeval tmp;

	parser(&conds, argc, argv);
	status = 1;
	i = 0;
	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * conds.n);
	if (!mutex)
		return (0);
	while (i < conds.n)
	{
		pthread_mutex_init(&(mutex[i]), NULL); // check for fail
		i++;
	}
	pthread_mutex_init(&writing, NULL);
	plato = (t_plato *)malloc(sizeof(t_plato) * conds.n); // same here
	i = 0;
	gettimeofday(&tmp, NULL);
	conds.starttime = tmp;
	conds.writing = &writing;
	while (i < conds.n)
	{
		gettimeofday(&(plato->last_eat), NULL);
		plato[i].last_eat = conds.starttime;
		plato[i].conds_cpy = &conds;
		plato[i].status = &status;
		plato[i].num = i;
		if (i == conds.n - 1)
		{
			plato[i].f = 0;
			plato[i].s = i;
		}
		else
		{
			plato[i].f = i;
			plato[i].s = i + 1;
		}
		plato[i].first = &(mutex[plato[i].f]);
		plato[i].second = &(mutex[plato[i].s]);
		// if (i % 2 == 1)
		// 	usleep(100);
		pthread_create(&plato[i].id, NULL, aristotle, &(plato[i]));
		i++;
	}
	while (status)
	{
		i = 0;
		while (i < conds.n)
		{
			pthread_mutex_lock(conds.writing);
			gettimeofday(&tmp, NULL);
			if (timedif(tmp, plato[i].last_eat) >= (long long)conds.die) // something wrong, dudes are immortal
			{
				ft_print(timedif(tmp, conds.starttime), *plato, 5);
				status = 0;
			}
			pthread_mutex_unlock(conds.writing);
			i++;
		}
	}
	i = 0;
	while (i < conds.n)
	{
		pthread_join(plato[i++].id, NULL);
	}
	free(mutex);
	free(plato);
	return (0);
}
