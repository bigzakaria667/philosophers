/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:50:46 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/08/05 17:38:02 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_simulation
{
	int		philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		time_to_think;
	int		nb_meals;
	int		dead;
	struct s_philo	**philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*dead_mutex;
}	t_simulation;

typedef struct s_philo
{
	pthread_t		thread;
	int			id;
	int			meals;
	int			last_meal;
	struct s_simulation	*simulation;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
}	t_philo;

/*----------------  philo.c  ---------------*/
void	philosophers(char **argv);
int	main(int argc, char **argv);

/*----------------  parsing.c  ---------------*/
int	ft_atoi(char *str);
int	check_numbers(char **argv);
int	parsing(char **argv);

/*----------------  initialisation.c  ---------------*/
t_philo		*init_philo(int id, t_simulation **simulation);
void		init_mutex(t_simulation **simulation);
void		init_simulation(t_simulation **simulation, char **argv);
void		give_fork(t_simulation **simulation);
void	initialisation(t_simulation **simulation, char **argv);

/*----------------  routine.c  ---------------*/
void	*thread_routine(void *arg);
void	is_sleeping(t_philo *philo);
void	is_eating(t_philo *philo);
void	is_thinking(t_philo *philo);
long	get_time_ms(void);

#endif
