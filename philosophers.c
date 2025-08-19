#include "philosophers.h"
#include <sys/wait.h>
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

void die(int i, struct timeval start)
{
	struct timeval tmp;

	gettimeofday(&tmp, NULL);
	printf("%lld: %d just died, you're a terrible parent!\n", timedif(tmp ,start), i);
	exit(0);
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
	pthread_mutex_lock(conds->writing);
	gettimeofday(&tmp, NULL);
	printf("bitcoin kashelyoki koder: %lld, %d\n", timedif(tmp, conds->starttime), plato->num);
	pthread_mutex_unlock(conds->writing);
	while (1)
	{
		pthread_mutex_lock(plato->first);
		pthread_mutex_lock(conds->writing);
		gettimeofday(&tmp, NULL);
		printf("%lld : %d took fork %d with his left hand\n", timedif(tmp, conds->starttime), plato->num, plato->f);
		pthread_mutex_unlock(conds->writing);
		pthread_mutex_lock(plato->second);
		pthread_mutex_lock(conds->writing);
		gettimeofday(&tmp, NULL);
		printf("%lld: %d took fork %d with his right hand\n", timedif(tmp, conds->starttime), plato->num, plato->s);
		gettimeofday(&tmp, NULL);
		printf("%lld: philosopher %d is eating\n", timedif(tmp, conds->starttime), plato->num);
		pthread_mutex_unlock(conds->writing);
		usleep(conds->eat * 1000);
		gettimeofday(&(plato->last_eat), NULL);
		i++;
		if (conds->fin > 0 && i >= conds->fin)
			*(plato->status) = 0;
		pthread_mutex_lock(conds->writing);
		gettimeofday(&tmp, NULL);
		printf("%lld : %d dropped forks %d and %d\n", timedif(tmp, conds->starttime), plato->num, plato->f, plato->s);
		pthread_mutex_unlock(conds->writing);
		pthread_mutex_unlock(plato->second);
		pthread_mutex_unlock(plato->first);
		usleep(conds->sleep * 1000);
		//pthread_mutex_lock(conds->writing);
	}
	return (NULL);
}
// when timeval usec reaches 1000000, it goes to 0, FIX THIS ARA
int main(int argc, char **argv)
{ // LIBFT IS ***NOT*** ALLOWED
	int i;
	pthread_t *id;
	t_plato	*plato;
	t_conds	*conds;
	pthread_mutex_t *mutex;
	pthread_mutex_t writing;
	int status;
	struct timeval tmp;

	conds = parser(argc, argv);
	if (!conds)
		return (0);
	status = 1;
	i = 0;
	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * conds->n);
	if (!mutex)
		return (0);
	id = (pthread_t *)malloc(sizeof(pthread_t) * conds->n);
	if (!id)
		return (free(mutex), 0);
	while (i < conds->n)
	{
		pthread_mutex_init(&(mutex[i]), NULL); // check for fail
		i++;
	}
	pthread_mutex_init(&writing, NULL);
	plato = (t_plato *)malloc(sizeof(t_plato) * conds->n); // same here
	i = 0;
	gettimeofday(&tmp, NULL);
	conds->starttime = tmp;
	conds->writing = &writing;
	while (i < conds->n)
	{
		gettimeofday(&(plato->last_eat), NULL);
		plato[i].last_eat = conds->starttime;
		plato[i].conds_cpy = conds;
		plato[i].status = &status;
		plato[i].num = i;
		if (i == conds->n - 1)
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
		pthread_create(&(id[i]), NULL, aristotle, &(plato[i]));
		i++;
	}
	while (status)
	{
		i = 0;
		while (i < conds->n)
		{
			pthread_mutex_lock(conds->writing);
			gettimeofday(&tmp, NULL);
			if (timedif(tmp, plato[i].last_eat) >= (long long)conds->die) // something wrong, dudes are immortal
			{
				printf("%lld\n", timedif(tmp, plato[i].last_eat));
				die(i, conds->starttime);
			}
			pthread_mutex_unlock(conds->writing);
			i++;
		}
	}
	i = 0;
	while (i < conds->n)
	{
		pthread_detach(id[i++]);
	}
	return (0);
}
