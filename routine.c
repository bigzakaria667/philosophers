/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:17:09 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/08/14 20:13:18 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_thinking(t_philo *philo)
{
	print_mutex("is thinking", philo);
	usleep(1000);
}

void	is_sleeping(t_philo *philo)
{
	print_mutex("is sleeping", philo);
	usleep(philo->simulation->time_to_sleep * 1000);
}

void	is_eating(t_philo *philo, pthread_mutex_t left_fork, pthread_mutex_t right_fork)
{
	pthread_mutex_lock(&left_fork);
	print_mutex("has taken a fork", philo);
	pthread_mutex_lock(&right_fork);
	print_mutex("has taken a fork", philo);
	pthread_mutex_lock(&philo->simulation->last_meal);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->simulation->last_meal);
	print_mutex("is eating", philo);
	usleep(philo->simulation->time_to_eat * 1000);
	pthread_mutex_unlock(&left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	philo->meals++;
	pthread_mutex_lock(&philo->simulation->count_meal);
	if (philo->simulation->nb_meals != -1 && philo->meals == philo->simulation->nb_meals)
		philo->simulation->global_meals++;
	pthread_mutex_unlock(&philo->simulation->count_meal);
}

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_time_ms();
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (check_death(philo->simulation) == 1)
			return (NULL);
		if (philo->id % 2 == 0)
			is_eating(philo, philo->left_fork, philo->right_fork);
		else
			is_eating(philo, philo->right_fork, philo->left_fork);
		if (check_death(philo->simulation) == 1)
			return (NULL);
		is_sleeping(philo);
		if (check_death(philo->simulation) == 1)
			return (NULL);
		is_thinking(philo);
		if (check_death(philo->simulation) == 1)
			return (NULL);
		if (check_meals(philo->simulation, philo->simulation->philos) == 1)
			return (NULL);
	}
	return (NULL);
}
