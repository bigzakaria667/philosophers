/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:59:14 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/07/22 22:04:38 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_simulation	init_simlation(char **argv)
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
	return (simulation);
}

t_philo		init_philo(char **argv, int id)
{
	t_philo	philo;

	philo.id = id;
	philo.meals = 0;
	return (philo);
}

t_simulation	initialisation(char **argv)
{
	t_simulation	simulation;
	int		i;

	i = 0;
	simulation = init_simulation(argv);
	while (i <= simulation->philos)
	{
		simulation->philo[i] = init_philo(argv, id);
		id++;
		i++;
	}
	return (simulation);
}
