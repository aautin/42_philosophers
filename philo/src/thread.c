/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:10:42 by aautin            #+#    #+#             */
/*   Updated: 2024/07/13 21:16:05 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "common.h"
#include "simulation.h"
#include "philo.h"
#include "thread.h"

/** * @retval the number of pthreads created by the monitoring pthread */
int	create_philos(pthread_t *threads, t_philo **philos, int philos_nb)
{
	int	i;

	i = 0;
	while (i < philos_nb)
	{
		if (pthread_create(&threads[i], NULL, &philosopher, philos[i]) != 0)
		{
			perror("create_philos():pthread_create()");
			return (i);
		}
		i++;
	}
	return (i);
}

void	stop_philos(t_sync_var **philos_status, int philos_to_join_nb)
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

void	join_philos(pthread_t *threads, int philos_to_join_nb)
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
