/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:17:09 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/08/13 18:36:41 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	check_meals(t_simulation *simulation)
{
	pthread_mutex_lock(simulation->dead_mutex);
	if (simulation->dead == 1)
	{
		pthread_mutex_unlock(simulation->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(simulation->dead_mutex);
	return (0);
}

void	is_thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->simulation->print);
	printf("%ld %d is thinking\n", get_time_ms() - philo->simulation->start_time, philo->id);
	pthread_mutex_unlock(philo->simulation->print);
	if (philo->simulation->philos % 2 != 0)
		usleep(philo->simulation->time_to_eat / 2 * 1000);
}

void	is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->simulation->print);
	printf("%ld %d is sleeping\n", get_time_ms() - philo->simulation->start_time, philo->id);
	pthread_mutex_unlock(philo->simulation->print);
	usleep(philo->simulation->time_to_sleep * 1000);
}

void	is_eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->simulation->print);
		printf("%ld %d has taken a fork \n", get_time_ms() - philo->simulation->start_time, philo->id);
		pthread_mutex_unlock(philo->simulation->print);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->simulation->print);
		printf("%ld %d has taken a fork \n", get_time_ms() - philo->simulation->start_time, philo->id);
		pthread_mutex_unlock(philo->simulation->print);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->simulation->print);
		printf("%ld %d has taken a fork \n", get_time_ms() - philo->simulation->start_time, philo->id);
		pthread_mutex_unlock(philo->simulation->print);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->simulation->print);
		printf("%ld %d has taken a fork\n", get_time_ms() - philo->simulation->start_time, philo->id);
		pthread_mutex_unlock(philo->simulation->print);
	}
	pthread_mutex_lock(philo->simulation->last_meal);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(philo->simulation->last_meal);
	pthread_mutex_lock(philo->simulation->print);
	printf("%ld %d is eating\n", get_time_ms() - philo->simulation->start_time, philo->id);
	pthread_mutex_unlock(philo->simulation->print);
	usleep(philo->simulation->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->meals++;
	pthread_mutex_lock(philo->simulation->count_meal);
	if (philo->simulation->nb_meals != -1 && philo->meals == philo->simulation->nb_meals)
		philo->simulation->global_meals++;
	pthread_mutex_unlock(philo->simulation->count_meal);
}

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_time_ms();
	if (philo->simulation->philos % 2 != 0)
		usleep(philo->simulation->time_to_eat / 2 * 1000);
	while (1)
	{
		if (check_meals(philo->simulation) == 1)
				return (NULL);
		is_eating(philo);
		if (check_meals(philo->simulation) == 1)
				return (NULL);
		is_sleeping(philo);
		if (check_meals(philo->simulation) == 1)
				return (NULL);
		is_thinking(philo);
		if (check_meals(philo->simulation) == 1)
				return (NULL);
		if (philo->simulation->nb_meals != -1)
		{
			pthread_mutex_lock(philo->simulation->count_meal);
			if (philo->simulation->global_meals == philo->simulation->philos)
			{
				pthread_mutex_unlock(philo->simulation->count_meal);
				return (NULL);
			}
		}
	}
	return (NULL);
}
