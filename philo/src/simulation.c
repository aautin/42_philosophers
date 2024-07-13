/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:44:50 by aautin            #+#    #+#             */
/*   Updated: 2024/07/13 22:04:46 by aautin           ###   ########.fr       */
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

static void	monitoring(t_monitor *monitor)
{
	int	i;

	i = monitor->philos_nb;
	while (i == monitor->philos_nb)
	{
		i = 0;
		while (i < monitor->philos_nb)
		{
			pthread_mutex_lock(&monitor->philos_status[i]->mutex);
			if (monitor->philos_status[i]->var == DEAD)
			{
				pthread_mutex_unlock(&monitor->philos_status[i]->mutex);
				break ;
			}
			pthread_mutex_unlock(&monitor->philos_status[i]->mutex);
			i++;
		}
	}
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

	monitoring(monitor);
	stop_philos(monitor->philos_status, monitor->philos_nb);
	join_philos(monitor->threads, monitor->philos_nb);
	return (SUCCESS);
}
