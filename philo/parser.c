/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:29:32 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/09/22 14:01:51 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	alt_atoi(const char *str)
{
	long	num;

	num = 0;
	if (*str == '0')
		return (printf("numbers should not start with 0\n"), 0);
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			num = 10 * num + *str - '0';
		else
			return (printf("arguments should be numbers\n"), 0);
		if (num > INT_MAX)
			return (printf("INT limit reached\n"), 0);
		str++;
	}
	return ((int)num);
}

static int	fill_struct(t_conds *res, int argc, char **argv)
{
	res->n = alt_atoi(argv[1]);
	if (!res->n)
		return (0);
	res->die = alt_atoi(argv[2]);
	if (!res->die)
		return (0);
	res->eat = alt_atoi(argv[3]);
	if (!res->eat)
		return (0);
	res->sleep = alt_atoi(argv[4]);
	if (!res->sleep)
		return (0);
	res->fin = -1;
	if (argc == 6)
		res->fin = alt_atoi(argv[5]);
	if (!res->fin)
		return (0);
	return (1);
}

t_conds	*parser(int argc, char **argv)
{
	t_conds	*conds;
	int		i;
	int		j;

	if (argc != 5 && argc != 6)
		return (printf("there should be 4 or 5 arguments\n"), NULL);
	conds = (t_conds *)malloc(sizeof (t_conds));
	if (!conds)
		return (NULL);
	i = 1;
	j = 0;
	while (argv[i])
	{
		if (!ft_isdigit(argv[i][j++]))
			return (free(conds), printf("arguments should be numbers\n"), NULL);
		if (!argv[i][j])
		{
			j = 0;
			i++;
		}
	}
	if (!fill_struct(conds, argc, argv))
		return (free(conds), NULL);
	return (conds);
}
