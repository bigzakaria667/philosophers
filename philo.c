/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:50:37 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/08/04 14:48:16 by zel-ghab         ###   ########.fr       */
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
}

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
		philosophers(argv);
	else
		return (1);
	return (0);
}
