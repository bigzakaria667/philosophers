/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:50:37 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/07/22 22:05:37 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosophers(char **argv)
{
	t_simulation	simulation;

	parsing(argv);
	simulation = initialisation(argv);
}

int	main(int argc, char **argv)
{
	if (argc != 4 || argc != 5)
		philosophers(argv);
	else
		return (1);
	return (0);
}
