/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:59:14 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/08/16 19:18:25 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philo(int id, t_simulation **simulation)
{
	t_philo		*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->simulation = *simulation;
	philo->id = id;
	philo->meals = 0;
	philo->last_meal = (*simulation)->start_time;
	return (philo);
}

void	give_fork(t_simulation	**simulation)
{
	int	i;

	i = 0;
	while (i < (*simulation)->philos)
	{
		(*simulation)->philo[i]->left_fork = &(*simulation)->fork[i];
		(*simulation)->philo[i]->right_fork = &(*simulation)->fork[(i + 1) % (*simulation)->philos];
		i++;
	}
}

int	init_mutex(t_simulation **simulation)
{
	int		i;

	i = 0;
	while (i < (*simulation)->philos)
	{	
		if (pthread_mutex_init(&(*simulation)->fork[i], NULL) != 0)
		{
			while (i >= 0)
			{	
				pthread_mutex_destroy(&(*simulation)->fork[i]);
				i--;
			}
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&(*simulation)->print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(*simulation)->dead_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(*simulation)->last_meal, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(*simulation)->count_meal, NULL) != 0)
		return (1);
	return (0);
}

int	init_simulation(t_simulation **simulation, char **argv)
{
	(*simulation)->philos = ft_atoi(argv[1]);
	(*simulation)->time_to_die = ft_atoi(argv[2]);
	(*simulation)->time_to_eat = ft_atoi(argv[3]);
	(*simulation)->time_to_sleep = ft_atoi(argv[4]);
	(*simulation)->time_to_think = 0;
	(*simulation)->global_meals = 0;
	(*simulation)->dead = 0;
	(*simulation)->start_time = get_time_ms();
	(*simulation)->philo = malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
	if (!(*simulation)->philo)
		return (1);
	if (argv[5])
		(*simulation)->nb_meals = ft_atoi(argv[5]);
	else
		(*simulation)->nb_meals = -1;
	(*simulation)->fork = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (!(*simulation)->fork)
		return (free_all(simulation), 1);
	if (init_mutex(simulation) == 1)
		return (free_all(simulation), 1);
	return (0);
}

int	initialisation(t_simulation **simulation, char **argv)
{
	int		i;

	if (init_simulation(simulation, argv) == 1)
		return (1);
	i = 0;
	while (i < (*simulation)->philos)
	{
		(*simulation)->philo[i] = init_philo(i + 1, simulation);
		if (!(*simulation)->philo[i])
		{
			while (i >= 0)
			{
				free((*simulation)->philo[i]);
				i--;
			}
			return (1);
		}
		i++;
	}
	give_fork(simulation);
	return (0);
}
