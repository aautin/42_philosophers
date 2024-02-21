/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:52:45 by aautin            #+#    #+#             */
/*   Updated: 2024/02/21 13:43:25 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define FREE 0
# define TAKEN 1

# define FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIED 4

typedef struct timeval	t_time;
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

typedef struct set_timers
{
	unsigned int	to_die;
	unsigned int	to_eat;
	unsigned int	to_sleep;
	t_time			start;
	t_time			lastmeal;
}	t_timers;

// philos_nb t_thread and forks, philos_nb+1 mutexs (1 for printf())
typedef struct s_table
{
	t_thread		*philos;
	char			*finished;
	t_mutex			*mutexs;
	char			*forks;
}	t_table;

typedef struct s_bag
{
	t_table			*table;

	t_timers		*time;
	unsigned short	*i;
	unsigned short	*philos_nb;
	int				*meals_left;
}	t_bag;

// utils.c
unsigned int	ft_atou(char *str_number);
void			printlog(t_mutex *mutex, t_time time, unsigned int i, char act);
void			change_finished_status(t_bag *bag, char new_status);
void			check_stop(t_bag *bag);

// bag.c
int				alloc_bag_components(t_bag *bag);
void			free_bag(t_bag *bag);

// table.c
void			set_finished(t_table *table, char statut, unsigned short nb);
int				set_table(t_table *table, unsigned short philos_nb);
void			free_table(t_table *table, unsigned short philos_nb);

//simulation.c
void			*simulation(void *adress);

// time.c
void			set_timers(t_timers *timers, char **argv);
int				is_time_to_die(t_bag *bag);
unsigned int	get_time_left(t_bag *bag);
void			kill_philo_during_action(t_bag *bag, int time, char act);		

// fork.c
int				are_forks_free(t_bag *bag);
void			free_forks(t_bag *bag);

#endif