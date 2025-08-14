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

void	*aristotle(void *v_plato)
{
	t_plato	*plato;
	int		i;

	i = 0;
	plato = (t_plato *)v_plato;
	while (plato->status)
	{
		pthread_mutex_lock(plato->left);
		//pthread_mutex_lock(plato->writing);
		printf("%d took fork %d with his left hand\n", plato->num, plato->num);
		//pthread_mutex_unlock(plato->writing);
		pthread_mutex_lock(plato->right);
		//pthread_mutex_lock(plato->writing);
		if (plato->num > 0)
			printf("%d took fork %d with his right hand\n", plato->num, plato->num - 1);
		else
			printf("%d took fork %d with his right hand\n", plato->num, 4);
		printf("philosopher %d is eating\n", plato->num);
		//pthread_mutex_unlock(plato->writing);
		usleep(plato->eat * 1000);
		i++;
		if (i >= 8)
			plato->status = 0;
		//pthread_mutex_lock(plato->writing);
		if (plato->num > 1)
			printf("%d dropped forks %d and %d\n", plato->num, plato->num, plato->num - 1);
		else
			printf("%d dropped forks %d and %d\n", plato->num, plato->num, 4);
		//pthread_mutex_unlock(plato->writing);
		pthread_mutex_unlock(plato->right);
		pthread_mutex_unlock(plato->left);
		usleep(plato->sleep * 1000);
	}
	return (NULL);

}

int	main(void)
{//LIBFT IS ***NOT*** ALLOWED 
	int	i;
	pthread_t	id[5];
	t_plato		*plato;
	pthread_mutex_t	mutex[5];
	pthread_mutex_t	writing;
	int	status;

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
		plato[i].eat = 100;
		plato[i].sleep = 50;
		plato[i].die = 200;
		plato[i].status = &status;
		plato[i].num = i;
		plato[i].left = &(mutex[i]);
		plato[i].right = &(mutex[4]);
		if (i > 0)
			plato[i].right = &(mutex[i - 1]);
		plato[i].writing = &writing;
		if (i == 4){
			plato[i].right = &(mutex[i]);
			plato[i].left = &(mutex[4]);
			if (i > 0)
				plato[i].left = &(mutex[i - 1]);
			plato[i].writing = &writing;
		}
		if (i % 2 == 1)
			usleep(10);
		pthread_create(&(id[i]), NULL, aristotle, &(plato[i]));
		i++;
	}
	while (status)
	{
		i = 0;
		while (i < 5)
			if (!plato[i++].status)
			{
				status = 0;
				break ;
			}
	}
	i = 0;
	while (i < 5)
		pthread_detach(id[i++]);
	return (0);
}
