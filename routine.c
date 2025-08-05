/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:17:09 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/08/05 17:13:49 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	is_thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->simulation->print);
	printf("%d is thinking...\n", philo->id);
	usleep(philo->simulation->time_to_think * 1000);
	pthread_mutex_unlock(philo->simulation->print);
}

void	is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->simulation->print);
	printf("%d is sleeping...\n", philo->id);
	usleep(philo->simulation->time_to_sleep * 1000);
	pthread_mutex_unlock(philo->simulation->print);
}

void	is_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	//printf("Philo %d a LOCKÉ right_fork à l'adresse %p\n", philo->id, philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	//printf("Philo %d a LOCKÉ left_fork à l'adresse %p\n", philo->id, philo->left_fork);
	pthread_mutex_lock(philo->simulation->print);
	printf("%d is eating\n", philo->id);
	pthread_mutex_unlock(philo->simulation->print);
	usleep(philo->simulation->time_to_eat * 1000);
	philo->meals++;
	pthread_mutex_lock(philo->simulation->print);
	printf("%d a fini de manger !\n", philo->id);
	pthread_mutex_unlock(philo->simulation->print);
	pthread_mutex_unlock(philo->left_fork);
	//printf("Philo %d a LIBERE left_fork à l'adresse %p\n", philo->id, philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	//printf("Philo %d a LIBERE right_fork à l'adresse %p\n", philo->id, philo->right_fork);
}

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(1000);
	while (philo->meals < 1)
	{
		// EAT
		is_eating(philo);
		philo->last_meal = get_time_ms();
		pthread_mutex_lock(philo->simulation->print);
		printf("Last meal : %d\n", philo->last_meal);
		pthread_mutex_unlock(philo->simulation->print);
		// SLEEP
		is_sleeping(philo);
		// THINK
		is_thinking(philo);
	}
	return (NULL);
}
