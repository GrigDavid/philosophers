/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:29:32 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/09/07 13:38:48 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int     alt_atoi(const char *str)
{
	long	num;

	num = 0;
	if (*str == '-' || *str == '+' || *str == '0')
		return (0);
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			num = 10 * num + *str - '0';
		else
			return (0);
		if (num > INT_MAX)
			return (0);
		str++;
	}
	return ((int)num);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (!ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-')
	{
		if ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
			i++;
		else
			return (0);
	}
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		num = 10 * num + str[i++] - '0';
	return (sign * num);
}

int	fill_struct(t_conds *res, int argc, char **argv)
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

t_conds	*parser(t_conds *res, int argc, char **argv)
{
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
	if (!fill_struct(res, argc, argv))
		return (NULL);
	return (res);
}
