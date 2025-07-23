/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:59:14 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/07/23 21:41:15 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		give_fork_right_left(t_simulation *simulation)
{
	int	i;

	i = 0;
}

void		init_fork(t_simulation **simulation)
{
	pthread_mutex_t	fork;
	int		error;
	int		i;

	i = 0;
	while (i <= simulation.philos)
	{
		error = pthread_mutex_init(&fork, NULL);
		if (error != 0)
			return ;
		simulation->fork[i] = fork;
		i++;
	}
}

t_philo		*init_philo(char **argv, t_simulation **simulation, int id)
{
	t_philo		philo;

	pthread_create(&simulation.philo, NULL, ..., NULL);
	philo.tid = tid;
	philo.id = id;
	philo.meals = 0;
	return (philo);
}

t_simulation	*init_simulation(char **argv)
{
	t_simulation	*simulation;

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

t_simulation	initialisation(char **argv)
{
	t_simulation	*simulation;
	int		i;
	int		id;

	id = 1;
	i = 0;
	simulation = init_simulation(argv);
	init_fork(&simulation);
	while (i <= simulation->philos)
	{
		simulation.philo[i] = init_philo(argv, &simulation, id);
		id++;
		i++;
	}
	return (simulation);
}
