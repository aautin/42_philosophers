/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/07/13 17:32:14 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "simulation.h"
#include "common.h"
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

	int	status = start_simulation(monitor);
	free_monitor(monitor, monitor->philos_nb);

	if (status == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
