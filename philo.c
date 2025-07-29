/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:50:37 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/07/28 21:41:00 by zel-ghab         ###   ########.fr       */
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

	printf("Nombres de philo : %d\n", simulation->philos);
	printf("Time to die : %d\n", simulation->time_to_die);
	printf("Time to eat : %d\n", simulation->time_to_eat);
	printf("Time to sleep : %d\n", simulation->time_to_sleep);
	printf("Nombre de meals : %d\n\n", simulation->nb_meals);

	while (i < simulation->philos)
	{
		printf("ID : %d\n", simulation->philo[i]->id);
		printf("Counter meals : %d\n", simulation->philo[i]->meals_count);
		printf("Right fork : %p\n", &simulation->philo[i]->right_fork);
		printf("Left fork : %p\n", &simulation->philo[i]->left_fork);
		printf("\n");
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
		philosophers(argv);
	else
		return (1);
	return (0);
}
