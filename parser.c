/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:29:32 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/08/26 13:49:35 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
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
	res->n = ft_atoi(argv[1]);
	res->die = ft_atoi(argv[2]);
	res->eat = ft_atoi(argv[3]);
	res->sleep = ft_atoi(argv[4]);
	res->fin = -1;
	if (argc == 6)
		res->fin = ft_atoi(argv[5]);
	return (res);
}
