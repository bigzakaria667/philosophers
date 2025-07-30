/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:17:09 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/07/30 21:58:57 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0 && philo->meals < 1)
	{
		if (pthread_mutex_lock(&philo->right_fork) == 0)
		{
			if (pthread_mutex_lock(&philo->left_fork) == 0)
			{
				printf("%d commence de manger !\n", philo->id);
				usleep(philo->simulation->time_to_eat);
				philo->meals++;
				printf("%d a fini de manger !\n", philo->id);
			}
			pthread_mutex_unlock(&philo->right_fork);
			pthread_mutex_unlock(&philo->left_fork);
		}
	}
	else if (philo->id % 2 != 0 && philo->meals < 1)
	{
		if (pthread_mutex_lock(&philo->left_fork) == 0)
		{
			if (pthread_mutex_lock(&philo->right_fork) == 0)
			{
				printf("%d commence de manger !\n", philo->id);
				usleep(philo->simulation->time_to_eat);
				philo->meals++;
				printf("%d a fini de manger !\n", philo->id);
			}
			pthread_mutex_unlock(&philo->right_fork);
			pthread_mutex_unlock(&philo->left_fork);		
		}
	}
}

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->meals < 1)
	{
		eat(philo);
	}
	return (NULL);
}
