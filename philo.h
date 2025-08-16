/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:50:46 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/08/16 20:48:56 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_simulation
{
	int					philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_think;
	long				start_time;
	int					nb_meals;
	int					global_meals;
	int					dead;
	struct s_philo		**philo;
	pthread_mutex_t		*fork;
	pthread_mutex_t		print;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		last_meal;
	pthread_mutex_t		count_meal;
	pthread_t			doctor;
}	t_simulation;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					meals;
	long				last_meal;
	struct s_simulation	*simulation;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
}	t_philo;

/*----------------  philo.c  ---------------*/
void	free_all(t_simulation **simulation);
int		thread_join(t_simulation **simulation);
int		start_thread(t_simulation **simulation);
int		philosophers(char **argv);
int		main(int argc, char **argv);

/*----------------  parsing.c  ---------------*/
int		ft_atoi(char *str);
int		check_limits(char **argv);
int		check_numbers(char **argv);
int		parsing(char **argv);

/*----------------  initialisation.c  ---------------*/
t_philo	*init_philo(int id, t_simulation **simulation);
void	give_fork(t_simulation **simulation);
int		init_mutex(t_simulation **simulation);
int		init_simulation(t_simulation **simulation, char **argv);
int		initialisation(t_simulation **simulation, char **argv);

/*----------------  routine.c  ---------------*/
void	*thread_routine(void *arg);
int		is_sleeping(t_philo *philo);
int		is_eating(t_philo *philo, \
	pthread_mutex_t *left_fork, pthread_mutex_t *right_fork);
int		is_thinking(t_philo *philo);

/*----------------  doctor.c  ---------------*/
void	*thread_doctor(void *arg);

/*----------------  utils.c  ---------------*/
long	get_time_ms(void);
int		check_death(t_simulation *simulation);
int		check_meals(t_simulation *simulation, int philos);
int		print_mutex(char *s, t_philo *philo);

#endif
