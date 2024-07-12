/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/07/13 01:18:09 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "config.h"
#include "monitor.h"

int	main(int argc, char *argv[])
{
	t_config	*config;

	config = get_config(argc - 1, argv + 1);
	if (config == NULL)
		return (EXIT_FAILURE);

	t_monitor	*monitor;
	monitor = get_monitor(config);
	free(config);
	if (monitor == NULL)
		return (EXIT_FAILURE);

	free(monitor->forks[0]);
	free(monitor->forks[1]);
	free(monitor->forks);
	free(monitor->philos[0]);
	free(monitor->philos[1]);
	free(monitor->philos);
	free(monitor->philos_status[0]);
	free(monitor->philos_status[1]);
	free(monitor->philos_status);
	free(monitor->printf);
	free(monitor->threads);
	free(monitor);

	return (EXIT_SUCCESS);
}
