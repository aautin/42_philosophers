/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:44:50 by aautin            #+#    #+#             */
/*   Updated: 2024/07/14 04:03:46 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "time.h"
#include "utils.h"
#include "thread.h"
#include "monitor.h"
#include "common.h"

#include <unistd.h>

void	kill_philo(t_sync_var *status, t_mutex *print, int timestamp, int philo_index)
{
	pthread_mutex_lock(&status->mutex);
	status->var = DEAD;
	pthread_mutex_unlock(&status->mutex);
	print_state(print, timestamp, philo_index, DIE);
}

void	*philosopher(void *param)
{
	t_philo	*philo;
	philo = param;

	gettimeofday(&philo->timestamp, NULL);
	philo->lastmeal = philo->timestamp;
	while (get_time_spend(philo->lastmeal) < philo->times.die)
	{
		if (take_forks(philo) == SUCCESS)
		{
			
		}	
	}
	kill_philo(philo->status, philo->print, get_time_spend(philo->timestamp),
		philo->index);
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
