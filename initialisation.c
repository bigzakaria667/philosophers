/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:59:14 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/07/24 16:41:39 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		give_fork_right_left(t_simulation **simulation)
{
	pthread_mutex_t	*fork;
	int		i;
	int		j;

	i = 0;
	j = 0;
	fork = (*simulation)->fork;
	while (i <= (*simulation)->philos)
	{
		(*simulation)->philo[i]->right_fork = fork[j++];
		(*simulation)->philo[i]->left_fork = fork[j];
	}
}

void		init_fork(t_simulation **simulation)
{
	pthread_mutex_t	fork;
	int		error;
	int		i;

	i = 0;
	while (i <= (*simulation)->philos)
	{
		error = pthread_mutex_init(&fork, NULL);
		if (error != 0)
			return ;
		(*simulation)->fork[i] = fork;
		i++;
	}
}

t_philo		*init_philo(int id)
{
	t_philo		*philo;

	philo = NULL;
	//pthread_create(&simulation.philo, NULL, ..., NULL);
	philo->id = id;
	philo->meals_count = 0;
	return (philo);
}

void	init_simulation(t_simulation **simulation, char **argv)
{
	(*simulation)->philos = ft_atoi(argv[1]);
	(*simulation)->time_to_die = ft_atoi(argv[2]);
	(*simulation)->time_to_eat = ft_atoi(argv[3]);
	(*simulation)->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		(*simulation)->nb_meals = 0;
	else
		(*simulation)->nb_meals = -1;
	(*simulation)->philo = malloc (sizeof(t_philo) * ft_atoi(argv[1]));
	(*simulation)->fork = malloc (sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
}

t_simulation	*initialisation(char **argv)
{
	t_simulation	*simulation;
	int		i;
	int		id;

	id = 1;
	i = 0;
	init_simulation(&simulation, argv);
	init_fork(&simulation);
	while (i <= simulation->philos)
	{
		simulation->philo[i] = init_philo(id);
		id++;
		i++;
	}
	give_fork_right_left(&simulation);
	return (simulation);
}
