/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:45:58 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/07/24 17:03:12 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					signe;
	unsigned long long	result;

	result = 0;
	i = 0;
	signe = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	return (result * signe);
}

int	check_numbers(char **argv)
{
	int	i;

	i = 2;
	if (ft_atoi(argv[i]) <= 0 || ft_atoi(argv[i]) > 200)
		return (1);
	while (ft_atoi(argv[i]) && i != 5)
	{
		if (ft_atoi(argv[i]) < 60 || ft_atoi(argv[i]) > 2147483647)
			return (1);
		i++;
	}
	if (argv[5])
	{
		if (ft_atoi(argv[5]) <= 0)
			return (1);
	}
	return (0);
}

int	parsing(char **argv)
{
	if (check_numbers(argv) == 1)
		return (1);
	return (0);
}
