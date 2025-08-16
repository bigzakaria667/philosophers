/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:18:04 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/08/06 17:16:26 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_doctor(void *arg)
{
	t_simulation	*simulation;
	int		i;
	int		time_to_die;

	simulation = (t_simulation *)arg;
	time_to_die = simulation->time_to_die;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&simulation->count_meal);
		if (simulation->global_meals == simulation->philos)
			break;
		pthread_mutex_unlock(&simulation->count_meal);
		pthread_mutex_lock(&simulation->last_meal);
		if (get_time_ms() - simulation->philo[i]->last_meal > time_to_die)
		{
			pthread_mutex_unlock(&simulation->last_meal);
			pthread_mutex_lock(&simulation->dead_mutex);
			simulation->dead = 1;
			pthread_mutex_unlock(&simulation->dead_mutex);
			pthread_mutex_lock(&simulation->print);
			printf("%ld %d died\n", get_time_ms() - simulation->start_time, i + 1);
			pthread_mutex_unlock(&simulation->print);
			return (pthread_mutex_unlock(&simulation->count_meal), NULL);
		}
		pthread_mutex_unlock(&simulation->last_meal);
		i++;
		if (i >= simulation->philos)
			i = 0;
		pthread_mutex_unlock(&simulation->count_meal);
	}
	return (NULL);
}
