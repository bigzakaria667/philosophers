/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:50:37 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/08/14 16:48:26 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	philosophers(char **argv)
{
	t_simulation	*simulation;

	if (parsing(argv) == 1)
		return (1); 
	simulation = malloc(sizeof(t_simulation));
	if (!simulation)
		return (1);
	initialisation(&simulation, argv);
	if (thread_join(&simulation) == 1)
		return (1);
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
