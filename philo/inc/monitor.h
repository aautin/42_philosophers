/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:52:45 by aautin            #+#    #+#             */
/*   Updated: 2024/07/13 00:50:21 by aautin           ###   ########.fr       */
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

t_monitor	*get_monitor(t_config *config);

#endif