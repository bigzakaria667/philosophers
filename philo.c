/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:50:37 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/08/16 19:26:12 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_simulation **simulation)
{
	int	i;

	i = 0;
	while (i < (*simulation)->philos)
	{
		free((*simulation)->philo[i]);
		(*simulation)->philo[i] = NULL;
		pthread_mutex_destroy(&(*simulation)->fork[i]);
		i++;
	}
	free((*simulation)->philo);
	(*simulation)->philo = NULL;
	free((*simulation)->fork);
	(*simulation)->fork = NULL;
	pthread_mutex_destroy(&(*simulation)->print);
	pthread_mutex_destroy(&(*simulation)->dead_mutex);
	pthread_mutex_destroy(&(*simulation)->last_meal);
	pthread_mutex_destroy(&(*simulation)->count_meal);
}

int	thread_join(t_simulation **simulation)
{
	int	i;

	i = 0;
	while (i < (*simulation)->philos)
	{
		if (pthread_join((*simulation)->philo[i]->thread, NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_join((*simulation)->doctor, NULL) != 0)
		return (1);
	return (0);
}

int	start_thread(t_simulation **simulation)
{
	int	i;

	i = 0;
	while (i < (*simulation)->philos)
	{
		if (pthread_create(&((*simulation)->philo[i]->thread), NULL, thread_routine, (*simulation)->philo[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&((*simulation)->doctor), NULL, thread_doctor, *simulation) != 0)
		return (1);
	return (0);
}

int	philosophers(char **argv)
{
	t_simulation	*simulation;

	if (parsing(argv) == 1)
		return (1); 
	simulation = malloc(sizeof(t_simulation));
	if (!simulation)
		return (1);
	if (initialisation(&simulation, argv) == 1)
		return (free(simulation), 1);
	if (start_thread(&simulation) == 1)
		return (free_all(&simulation), free(simulation), 1);
	if (thread_join(&simulation) == 1)
		return (free_all(&simulation), free(simulation), 1);
	free_all(&simulation);
	free(simulation);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (philosophers(argv) == 1)
			return (printf("Error\n"), 1);
	}
	else
		return (printf("Error\n"), 1);
	return (0);
}
