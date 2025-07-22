/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:59:14 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/07/22 20:14:10 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_simulation(char **argv)
{
	t_simulation	simulation;

	simulation.philos = argv[1];
	simulation.time_to_die = argv[2];
	simulation.time_to_eat = argv[3];
	simulation.time_to_sleep = argv[4];
	if (argc == 5)
		simulation.nb_meals = 0;
	else
		simulation.nb_meals = -1;
}

void	init_philo(char **argv, int *id)
{
	t_philo	philo;

	id = 0;
	while (id != argv[1])
	{

		id++:
	}
}

void	initialisation(char **argv)
{
	int	id;

	id = 0;
	init_simulation(argv);
	init_philo(argv, &id);
}
