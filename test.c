#include "philosophers.h"

typedef struct s_data
{
	pthread_mutex_t	*p;
	int				num;
} t_data;

void	*fun(void *datark)
{
	t_data	*data = datark;
	pthread_mutex_lock((data->p));
	while (data->num < 100)
	{
		
		data->num++;
		write(1, "_",1	);
	}
	pthread_mutex_unlock((data->p));
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t		tid;
	int	a;
	//pthread_mutex_t	pa;
	t_data			data;

	a=0;
	data.p = malloc(sizeof(pthread_mutex_t));
	if (!data.p)
		return (1);
	data.num = 0;
	pthread_create(&tid, 0, fun, &data);
	while (data.num < 100)
	{
		pthread_mutex_lock((data.p));
		ft_putnbr_fd(data.num, 1);
		write(1, "\n", 1);
		pthread_mutex_unlock((data.p));
		a++;
	}
	pthread_join(tid, NULL);
	(void)argc;
	(void)argv;
	(void)a;
	return (0);
}