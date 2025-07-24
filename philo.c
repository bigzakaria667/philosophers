/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:50:37 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/07/24 16:55:35 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosophers(char **argv)
{
	t_simulation	*simulation;

	parsing(argv);
	simulation = initialisation(argv);
	printf("%d", simulation->philos);
	printf("%d", simulation->time_to_die);
	printf("%d", simulation->time_to_eat);
	printf("%d", simulation->time_to_sleep);
	printf("%d", simulation->nb_meals);
}

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
		philosophers(argv);
	else
		return (1);
	return (0);
}
