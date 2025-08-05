/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:17:09 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/08/05 15:05:58 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
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
	usleep(philo->simulation->time_to_eat * 1000);
}

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(1000);
	while (philo->meals < 2)
		eat(philo);
	return (NULL);
}
