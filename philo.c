/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:50:37 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/07/30 21:03:48 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosophers(char **argv)
{
	t_simulation	*simulation;
	
	int i = 0;
	parsing(argv);
	simulation = malloc(sizeof(t_simulation));
	if (!simulation)
		return ;
	initialisation(&simulation, argv);
	while (simulation->philo[i])
	{
		pthread_join(simulation->philo[i]->thread, NULL);
		i++;
	}
	// PRINT
	//printf("\nNombres de philo : %d\n", simulation->philos);
	//printf("Time to die : %d\n", simulation->time_to_die);
	//printf("Time to eat : %d\n", simulation->time_to_eat);
	//printf("Time to sleep : %d\n", simulation->time_to_sleep);
	//printf("Time to think : %d\n", simulation->time_to_think);
	//printf("Nombre de meals : %d\n\n", simulation->nb_meals);

	/*while (i < simulation->philos)
	{
		printf("ID : %d\n", simulation->philo[i]->id);
		printf("Counter meals : %d\n", simulation->philo[i]->meals_count);
		printf("\n");
		i++;
	}*/
}

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
		philosophers(argv);
	else
		return (1);
	return (0);
}
