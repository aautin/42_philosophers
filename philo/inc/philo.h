/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:52:45 by aautin            #+#    #+#             */
/*   Updated: 2024/07/18 20:24:10 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "thread.h"
# include "time.h"

typedef enum e_sim_status {
	WAIT = -2,
	NO_MEALS_LIMIT = -1,
	EXIT = 0
}	t_sim_status;

# define FREE			0
# define TAKEN			1

typedef enum e_activity
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_activity;

typedef struct s_philosopher {
	t_times		times;
	t_time		timestamp;
	t_time		lastmeal;
	int			meals_to_eat;
	int			philos_nb;
	int			index;

	t_mutex		*print;
	t_sync_var	*sim_status;
	t_sync_var	*left_fork;
	t_sync_var	*right_fork;
}	t_philo;

void	kill_philo(t_sync_var *status, t_mutex *print, t_time timestamp,
			int philo_index);
int		should_philo_stop(t_philo *philo);
void	*philosopher(void *param);

#endif