#include "philosophers.h"
#include <sys/wait.h>
//skzbi hamar n = 5; eat = 100; sleep = 50; die = 200
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

void	die(int i)
{
	printf("%d just died, you're a terrible parent!\n", i);
	exit(0);
}

void	*aristotle(void *v_plato)
{
	struct timeval tmp;
	t_plato	*plato;
	int		i;

	i = 0;
	plato = (t_plato *)v_plato;
	while (plato->status)
	{
		pthread_mutex_lock(plato->left);
		gettimeofday(&tmp, NULL);
		//pthread_mutex_lock(plato->writing);
		printf("%d : %d took fork %d with his left hand\n", (int)tmp.tv_usec, plato->num, plato->l);
		//pthread_mutex_unlock(plato->writing);
		pthread_mutex_lock(plato->right);
		gettimeofday(&tmp, NULL);
		//pthread_mutex_lock(plato->writing);
		printf("%d: %d took fork %d with his right hand\n", (int)tmp.tv_usec, plato->num, plato->r);
		printf("%d: philosopher %d is eating\n", (int)tmp.tv_usec, plato->num);
		//pthread_mutex_unlock(plato->writing);
		usleep(plato->eat * 1000);
		gettimeofday(&(plato->last_eat), NULL);
		i++;
		if (i >= 8)
			plato->status = 0;
		//pthread_mutex_lock(plato->writing);
		printf("%d : %d dropped forks %d and %d\n", (int)plato->last_eat.tv_usec, plato->num, plato->l, plato->r);
		//pthread_mutex_unlock(plato->writing);
		pthread_mutex_unlock(plato->right);
		pthread_mutex_unlock(plato->left);
		usleep(plato->sleep * 1000);
	}
	return (NULL);
}
//when timeval usec reaches 1000000, it goes to 0, FIX THIS ARA
int	main(void)
{//LIBFT IS ***NOT*** ALLOWED
	int				i;
	pthread_t		id[5];
	t_plato			*plato;
	pthread_mutex_t	mutex[5];
	pthread_mutex_t	writing;
	int				status;
	struct timeval	tmp;
	

	status = 1;
	i = 0;
	while (i < 5)
	{
		pthread_mutex_init(&(mutex[i]), NULL); //check for fail
		i++;
	}
	pthread_mutex_init(&writing, NULL); 
	plato = (t_plato *)malloc(sizeof(t_plato) * 5); //same here
	i = 0;
	while (i < 5)
	{
		gettimeofday(&(plato->last_eat), NULL);
		plato[i].eat = 200;
		plato[i].sleep = 200;
		plato[i].die = 800;
		plato[i].status = &status;
		plato[i].num = i;
		if (i == 4)
		{
			plato[i].l = 0;
			plato[i].r = i;
		}
		else
		{
			plato[i].r = i;
			plato[i].l = i + 1;
		}
		plato[i].left = &(mutex[plato[i].l]);
		plato[i].right = &(mutex[plato[i].r]);
		plato[i].writing = &writing;
		// if (i % 2 == 1)
		// 	usleep(100);
		pthread_create(&(id[i]), NULL, aristotle, &(plato[i]));
		i++;
	}
	while (status)
	{
		i = 0;
		while (i < 5)
		{
			gettimeofday(&tmp, NULL);
			if (tmp.tv_usec - plato[i].last_eat.tv_usec >= plato[i].die * 1000)
				die(i);
			i++;
		}
	}
	i = 0;
	while (i < 5)
		pthread_detach(id[i++]);
	return (0);
}
