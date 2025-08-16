/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:17:09 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/08/16 20:27:34 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_thinking(t_philo *philo)
{
	if (print_mutex("is thinking", philo) == 1)
		return (1);
	usleep(1000);
	return (0);
}

int	is_sleeping(t_philo *philo)
{
	if (print_mutex("is sleeping", philo) == 1)
		return (1);
	usleep(philo->simulation->time_to_sleep * 1000);
	return (0);
}

int	is_eating(t_philo *philo, pthread_mutex_t *left_fork,
		pthread_mutex_t *right_fork)
{
	pthread_mutex_lock(left_fork);
	if (print_mutex("has taken a fork", philo) == 1)
		return (pthread_mutex_unlock(left_fork), 1);
	pthread_mutex_lock(right_fork);
	if (print_mutex("has taken a fork", philo) == 1)
		return (pthread_mutex_unlock(left_fork),
			pthread_mutex_unlock(right_fork), 1);
	pthread_mutex_lock(&philo->simulation->last_meal);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->simulation->last_meal);
	if (print_mutex("is eating", philo) == 1)
		return (pthread_mutex_unlock(left_fork),
			pthread_mutex_unlock(right_fork), 1);
	usleep(philo->simulation->time_to_eat * 1000);
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
	philo->meals++;
	pthread_mutex_lock(&philo->simulation->count_meal);
	if (philo->simulation->nb_meals != -1
		&& philo->meals == philo->simulation->nb_meals)
		philo->simulation->global_meals++;
	pthread_mutex_unlock(&philo->simulation->count_meal);
	return (0);
}

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (philo->id % 2 == 0)
		{
			if (is_eating(philo, philo->left_fork, philo->right_fork) == 1)
				return (NULL);
		}
		else
		{
			if (is_eating(philo, philo->right_fork, philo->left_fork) == 1)
				return (NULL);
		}
		if (is_sleeping(philo) == 1)
			return (NULL);
		if (is_thinking(philo) == 1)
			return (NULL);
		if (check_meals(philo->simulation, philo->simulation->philos) == 1)
			return (NULL);
	}
	return (NULL);
}
