/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:52:45 by aautin            #+#    #+#             */
/*   Updated: 2024/07/13 14:39:27 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H

# include "philo.h"
# include "thread.h"

typedef struct s_monitoring_pthread {
	pthread_t	*threads;

	t_philo		**philos;

	t_sync_var	**forks;
	t_sync_var	**philos_status;

	t_mutex		*printf;
}	t_monitor;

int			are_sync_vars_mallocated(t_sync_var **philos_status, t_sync_var **forks, int philos_nb);
int			are_philos_mallocated(t_philo **philos, int philos_nb);

void		free_monitor(t_monitor *monitor, int philos_nb);
void		init_monitor(t_monitor *monitor, t_config *config);
t_monitor	*get_monitor(t_config *config);

#endif