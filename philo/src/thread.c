/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:10:42 by aautin            #+#    #+#             */
/*   Updated: 2024/07/20 19:53:11 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "common.h"
#include "fork.h"
#include "philo.h"
#include "thread.h"

/** * @retval the number of pthreads created by the monitoring pthread */
int	create_threads(pthread_t *threads, t_philo **philos, int philos_nb)
{
	int	i;

	i = 0;
	while (i < philos_nb)
	{
		if (pthread_create(&threads[i], NULL, &philosopher, philos[i]) != 0)
		{
			perror("create_threads():pthread_create()");
			return (i);
		}
		i++;
	}
	return (i);
}

void	stop_threads(t_sync_var *sim_status)
{
	pthread_mutex_lock(&sim_status->mutex);
	sim_status->var = EXIT;
	pthread_mutex_unlock(&sim_status->mutex);
}

void	join_threads(pthread_t *threads, int philos_nb)
{
	void	*buffer;
	int		i;

	i = 0;
	while (i < philos_nb)
	{
		if (pthread_join(threads[i], &buffer) != 0)
			perror("join_threads():pthread_join()");
		i++;
	}
}
