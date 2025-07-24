/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:50:46 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/07/24 16:41:20 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_simulation
{
	int		philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_meals;
	struct s_philo	**philo;
	pthread_mutex_t	*fork;
}	t_simulation;

typedef struct s_philo
{
	pthread_t		philo;
	int			id;
	int			meals_count;
	struct s_simulation	simulation;
	pthread_mutex_t		right_fork;
	pthread_mutex_t		left_fork;
}	t_philo;

/*----------------  philo.c  ---------------*/
void	philosophers(char **argv);
int	main(int argc, char **argv);

/*----------------  parsing.c  ---------------*/
int	ft_atoi(const char *str);
int	check_numbers(char **argv);
int	parsing(char **argv);

/*----------------  initialisation.c  ---------------*/
void		give_fork_right_left(t_simulation **simulation);
void		init_fork(t_simulation **simulation);
t_philo		*init_philo(int id);
void		init_simulation(t_simulation **simulation, char **argv);
t_simulation	*initialisation(char **argv);

#endif
