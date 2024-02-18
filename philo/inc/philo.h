/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:52:45 by aautin            #+#    #+#             */
/*   Updated: 2024/02/18 19:57:46 by aautin           ###   ########.fr       */
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
	t_mutex			*mutexs;
	char			*forks;
}	t_table;

typedef struct s_bag
{
	t_table			*table;

	t_timers		*time;
	unsigned short	*i;
	unsigned short	*philos_nb;
}	t_bag;

// utils.c
int			ft_atou(char *str_number);
void		printlog(t_mutex *mutex, t_time start, unsigned int i, char action);
void		kill_philo_during_action(t_bag *bag, int timeleft, char action);

// config.c
void		set_timers(t_timers *timers, char **argv);
int			set_table(t_table *table, unsigned short philos_nb);
void		free_table(t_table *table, unsigned short philos_nb);
void		free_bag(t_bag *bag);

//simulation.c
void		*simulation(void *adress);

// time.c
int				is_time_to_die(t_bag *bag);
unsigned int	get_time_left(t_bag *bag);

#endif