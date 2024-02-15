/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:52:45 by aautin            #+#    #+#             */
/*   Updated: 2024/02/15 17:04:33 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define FREE 0
# define TAKEN 1

typedef struct timeval	t_time;
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

typedef struct s_config
{
	t_thread		*philos;
	t_mutex			*mutexs;
	t_time			start;
	t_time			now;
	char			*forks;
	int				philos_nb;
	int				to_die;
	int				to_eat;
	int				to_sleep;
}	t_config;

typedef struct s_baggage
{
	t_config	*config;
	int			i;
}	t_baggage;

// utils.c
int			ft_atoi(char *str_number);
t_time		get_current_time(t_config *config);

// config.c
void		set_times(t_config *config, char **argv);
int			set_forks(t_config *config);
void		free_config(t_config *config);

//simulation.c
void		*simulation(void *adress);

#endif