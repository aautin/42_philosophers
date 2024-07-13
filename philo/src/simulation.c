/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:44:50 by aautin            #+#    #+#             */
/*   Updated: 2024/07/13 18:11:14 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "thread.h"
#include "monitor.h"
#include "common.h"

static void	*start_philosopher(void *param)
{
	t_philo const	*philo = param;
	(void) philo;
	return (NULL);
}

/** * @retval the number of pthreads created by the monitoring pthread */
static int	create_philos(pthread_t *threads, t_philo **philos, int philos_nb)
{
	int	i;

	i = 0;
	while (i < philos_nb)
	{
		if (pthread_create(&threads[i], NULL, &start_philosopher, philos[i]) != 0)
		{
			perror("create_philos():pthread_create()");
			return (i);
		}
		i++;
	}
	return (i);
}

static void	stop_philos(t_sync_var **philos_status, int philos_to_join_nb)
{
	int		i;

	i = 0;
	while (i < philos_to_join_nb)
	{
		pthread_mutex_lock(&philos_status[i]->mutex);
		philos_status[i]->var = EXIT;
		pthread_mutex_unlock(&philos_status[i]->mutex);
		i++;
	}
}

static void	join_philos(pthread_t *threads, int philos_to_join_nb)
{
	void	*buffer;
	int		i;

	i = 0;
	while (i < philos_to_join_nb)
	{
		if (pthread_join(threads[i], &buffer) != 0)
			perror("join_philos():pthread_join()");
		i++;
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
	join_philos(monitor->threads, monitor->philos_nb);
	return (SUCCESS);
}
