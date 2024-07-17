/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:52:45 by aautin            #+#    #+#             */
/*   Updated: 2024/07/17 18:10:36 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "thread.h"
# include "time.h"

# define NO_MEALS_LIMIT	-1
# define DEAD			-2
# define EXIT			-3

# define FREE			0
# define TAKEN			1

typedef enum e_state
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_state;

typedef struct s_philosopher {
	t_times		times;
	t_time		timestamp;
	t_time		lastmeal;
	int			philos_nb;
	int			index;

	t_mutex		*print;
	t_sync_var	*status;
	t_sync_var	*left_fork;
	t_sync_var	*right_fork;
}	t_philo;

void	kill_philo(t_sync_var *status, t_mutex *print, t_time timestamp,
			int philo_index);
int		should_philo_stop(t_philo *philo);
void	*philosopher(void *param);

#endif