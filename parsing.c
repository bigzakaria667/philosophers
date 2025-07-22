/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:45:58 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/07/22 17:44:52 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_numbers(char **argv)
{
	int	i;

	i = 2;
	if (argv[0] <= 0 || argv[0] < 200)
		return (1);
	while (argv[i] && i != 5)
	{
		if (argv[i] < 60 || argv[i] > 2147483647)
			return (1);
		i++;
	}
	if (argv[5])
	{
		if (argv[5] <= 0)
			return (1);
	}
	return (0);
}

void	parsing(char **argv)
{
	if (check_numbers(argv) == 1)
		return (1);
	return (0);
}
