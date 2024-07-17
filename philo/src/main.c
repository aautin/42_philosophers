/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/07/17 18:16:08 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "fork.h"
#include "common.h"
#include "config.h"
#include "monitor.h"

static int	start_simulation(t_monitor *monitor)
{
	int const	created_philos_nb = create_threads(monitor->threads,
			monitor->philos, monitor->philos_nb);

	if (created_philos_nb != monitor->philos_nb)
	{
		stop_threads(monitor->philos_status, created_philos_nb);
		join_threads(monitor->threads, created_philos_nb);
		return (FAILURE);
	}
	monitoring(monitor);
	stop_threads(monitor->philos_status, monitor->philos_nb);
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
	status = start_simulation(monitor);
	free_monitor(monitor, monitor->philos_nb);
	if (status == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
