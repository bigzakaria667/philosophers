/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:21:08 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/07/29 19:10:10 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	think(t_philo *philo)
{
	int	time_to_sleep;

	time_to_sleep = philo->simulation->time_to_sleep;
	usleep(time_to_sleep);
	printf("%d %d is thinking\n", time_to_sleep, philo->id);
}
