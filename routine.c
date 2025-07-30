/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:17:09 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/07/29 19:42:33 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// 1er ETAPE : PRENDRE DEUX FORKS
	if (phthread_mutex_lock(philo->righ_fork) != 0)
		return ;
	if (phthread_mutex_lock(philo->left_fork) != 0)
		return ;
	return (NULL);
}
