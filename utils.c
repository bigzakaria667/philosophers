/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:27:30 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/08/14 20:02:02 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_mutex(char *s, t_philo *philo)
{
	pthread_mutex_lock(&philo->simulation->print);
	printf("%ld %d %s\n", get_time_ms() - philo->simulation->start_time, philo->id, s);
	pthread_mutex_unlock(&philo->simulation->print);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	check_death(t_simulation *simulation)
{
	pthread_mutex_lock(&simulation->dead_mutex);
	if (simulation->dead == 1)
	{
		pthread_mutex_unlock(&simulation->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&simulation->dead_mutex);
	return (0);
}

int	check_meals(t_simulation *simulation, int philos)
{
	if (simulation->nb_meals != -1)
	{
		pthread_mutex_lock(&simulation->count_meal);
		if (simulation->global_meals == philos)
		{
			pthread_mutex_unlock(&simulation->count_meal);
			return (1);
		}
		pthread_mutex_unlock(&simulation->count_meal);
	}
	return (0);
}
