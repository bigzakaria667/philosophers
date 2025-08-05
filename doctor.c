/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:18:04 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/08/05 18:28:12 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_doctor(void *arg)
{
	t_simulation	*simulation;
	int		i;
	int		time_to_die;

	simulation = (t_simulation *)arg;
	i = 0;
	time_to_die = simulation->time_to_die;
	while (simulation->dead != 1)
	{
		pthread_mutex_lock(simulation->dead_mutex);
		if (get_time_ms() - simulation->philo[i]->last_meal > time_to_die)
			simulation->dead = 1;
		pthread_mutex_unlock(simulation->dead_mutex);
		i++;
		if (i == simulation->philos)
			i = 0;
	}
	return (NULL);
}
