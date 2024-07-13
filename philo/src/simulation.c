/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:44:50 by aautin            #+#    #+#             */
/*   Updated: 2024/07/13 21:36:40 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"
#include "monitor.h"
#include "common.h"

void	*philosopher(void *param)
{
	t_philo const	*philo = param;
	(void) philo;
	return (NULL);
}

void	monitor(t_monitor *monitor)
{
	(void) monitor;
}

int	start_simulation(t_monitor *monitor)
{
	int const	created_philos_nb = create_philos(monitor->threads, monitor->philos, monitor->philos_nb);

	if (created_philos_nb != monitor->philos_nb)
	{
		stop_philos(monitor->philos_status, created_philos_nb);
		join_philos(monitor->threads, created_philos_nb);
		return (FAILURE);
	}
	join_philos(monitor->threads, monitor->philos_nb);
	return (SUCCESS);
}
