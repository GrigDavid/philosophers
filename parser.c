#include "philosophers.h"

t_conds	*parser(int argc, char **argv)
{
	t_conds	*res;
	int		i;
	int		j;

	if (argc != 5 && argc != 6)
		return (NULL);
	i = 1;
	j = 0;
	while (argv[i])
	{
		if (!ft_isdigit(argv[i][j++]))
			return (NULL);
		if (!argv[i][j])
		{
			j = 0;
			i++;
		}
	}
	if (i != argc)
		return (NULL);
	res = (t_conds *)malloc(sizeof(t_conds));
	if (!res)
		return (NULL);
	res->n = ft_atoi(argv[1]);
	res->die = ft_atoi(argv[2]);
	res->eat = ft_atoi(argv[3]);
	res->sleep = ft_atoi(argv[4]);
	res->fin = -1;
	if (argc == 6)
		res->fin = ft_atoi(argv[5]);
	return (res);
}