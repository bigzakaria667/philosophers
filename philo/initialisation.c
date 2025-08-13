/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:59:14 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/08/13 18:18:57 by zel-ghab         ###   ########.fr       */
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
	int	philos;

	i = 0;
	philos = (*simulation)->philos;
	while (i < philos)
	{
		(*simulation)->philo[i]->left_fork = &(*simulation)->fork[i];
		(*simulation)->philo[i]->right_fork = &(*simulation)->fork[(i + 1) % philos];
		i++;
	}
}

void	init_mutex(t_simulation **simulation)
{
	int		i;

	i = 0;
	while (i < (*simulation)->philos)
	{	
		if (pthread_mutex_init(&(*simulation)->fork[i], NULL) != 0)
			return ;
		i++;
	}
	(*simulation)->print = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init((*simulation)->print, NULL) != 0)
		return ;
	(*simulation)->dead_mutex = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init((*simulation)->dead_mutex, NULL) != 0)
		return ;
	(*simulation)->last_meal = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init((*simulation)->last_meal, NULL) != 0)
		return ;
	(*simulation)->count_meal = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init((*simulation)->count_meal, NULL) != 0)
		return ;
}

void	init_simulation(t_simulation **simulation, char **argv)
{
	if (ft_atoi(argv[1]) == 0)
		return ;
	(*simulation)->philos = ft_atoi(argv[1]);
	(*simulation)->time_to_die = ft_atoi(argv[2]);
	(*simulation)->time_to_eat = ft_atoi(argv[3]);
	(*simulation)->time_to_sleep = ft_atoi(argv[4]);
	(*simulation)->time_to_think = 0;
	(*simulation)->global_meals = 0;
	(*simulation)->dead = 0;
	if (argv[5])
		(*simulation)->nb_meals = ft_atoi(argv[5]);
	else
		(*simulation)->nb_meals = -1;
	(*simulation)->fork = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (!(*simulation)->fork)
		return ;
}

void	initialisation(t_simulation **simulation, char **argv)
{
	int		i;
	int		id;

	id = 1;
	i = 0;
	init_simulation(simulation, argv);
	(*simulation)->start_time = get_time_ms();
	init_mutex(simulation);
	(*simulation)->philo = malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
	if (!(*simulation)->philo)
		return ;
	while (i < (*simulation)->philos)
	{
		(*simulation)->philo[i] = init_philo(id, simulation);
		id++;
		i++;
	}
	give_fork(simulation);
	i = 0;
	while (i < (*simulation)->philos)
	{
		if (pthread_create(&((*simulation)->philo[i]->thread), NULL, thread_routine, (*simulation)->philo[i]) != 0)
			return ;
		i++;
	}
	if (pthread_create(&((*simulation)->doctor), NULL, thread_doctor, *simulation) != 0)
		return ;
}
