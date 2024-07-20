/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/07/20 19:51:41 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "fork.h"
#include "common.h"
#include "config.h"
#include "monitor.h"

int	get_simulation_status(t_sync_var *start)
{
	int	simulation_status;

	pthread_mutex_lock(&start->mutex);
	simulation_status = start->var;
	pthread_mutex_unlock(&start->mutex);
	return (simulation_status);
}

static void	start_simulation(t_sync_var *start, int philos_nb)
{
	pthread_mutex_lock(&start->mutex);
	start->var = philos_nb;
	pthread_mutex_unlock(&start->mutex);
}

static int	prepare_simulation(t_monitor *monitor)
{
	int	created_philos_nb;

	created_philos_nb = create_threads(monitor->threads,
			monitor->philos, monitor->philos_nb);
	if (created_philos_nb != monitor->philos_nb)
	{
		stop_threads(monitor->sim_status);
		join_threads(monitor->threads, created_philos_nb);
		return (FAILURE);
	}
	start_simulation(monitor->sim_status, monitor->philos_nb);
	monitoring(monitor);
	stop_threads(monitor->sim_status);
	join_threads(monitor->threads, monitor->philos_nb);
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_config	*config;
	t_monitor	*monitor;
	int			status;

	config = get_config(argc - 1, argv + 1);
	if (config == NULL)
		return (EXIT_FAILURE);
	monitor = get_monitor(config);
	free(config);
	if (monitor == NULL)
		return (EXIT_FAILURE);
	status = prepare_simulation(monitor);
	free_monitor(monitor, monitor->philos_nb);
	if (status == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
