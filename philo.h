/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:50:46 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/07/22 21:59:42 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_simulation
{
	int	philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_meals;
	// TABLEAU DE PHILO
	t_philo	philo[philos];
}	t_simulation;

typedef struct s_philo
{
	int		id;
	int		meals;
	t_simulation	simulation;
}	t_philo;

#endif
