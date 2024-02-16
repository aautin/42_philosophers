/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:52:45 by aautin            #+#    #+#             */
/*   Updated: 2024/02/16 16:17:45 by aautin           ###   ########.fr       */
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

typedef struct s_i
{
	int			i;
	int			right;
}	t_i;

typedef struct s_config
{
	t_thread		*philos;
	t_mutex			*mutexs;
	t_time			*meals;
	t_time			start;
	char			*forks;
	int				philos_nb;
	int				to_die;
	int				to_eat;
	int				to_sleep;
}	t_config;

typedef struct s_baggage
{
	t_config	*config;
	t_i			i;
}	t_baggage;

// utils.c
int			ft_atoi(char *str_number);
void		print_log(t_time start, int philo_i, char action);

// config.c
void		set_times(t_config *config, char **argv);
int			set_table(t_config *config);
void		set_indexs(t_baggage *bag, int i);
void		free_config(t_config *config);

//simulation.c
void		*simulation(void *adress);

// time.c
int			is_time_to_die(t_baggage *bag);

#endif