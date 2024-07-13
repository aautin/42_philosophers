/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/07/13 14:49:04 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "config.h"
#include "monitor.h"
#include "utils.h"

int	are_sync_vars_mallocated(t_sync_var **philos_status, t_sync_var **forks, int philos_nb)
{
	int	i;

	if (philos_status == NULL || forks == NULL)
		return (FALSE);

	i = 0;
	while (i < philos_nb)
	{
		if (philos_status[i] == NULL || forks[i] == NULL)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	are_philos_mallocated(t_philo **philos, int philos_nb)
{
	int	i;

	if (philos == NULL)
		return (FALSE);

	i = 0;
	while (i < philos_nb)
	{
		if (philos[i] == NULL)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	free_monitor(t_monitor *monitor, int philos_nb)
{
	free(monitor->threads);
	if (monitor->philos != NULL)
		free_double_tab((void **) monitor->philos, philos_nb);
	if (monitor->forks != NULL)
		free_double_tab((void **) monitor->forks, philos_nb);
	if (monitor->philos_status != NULL)
		free_double_tab((void **) monitor->philos_status, philos_nb);
	free(monitor->printf);
	free(monitor);
}

t_monitor	*get_monitor(t_config *config)
{
	t_monitor	*monitor;
	monitor = malloc(sizeof(*monitor));
	if (monitor == NULL)
		return (NULL);

	monitor->philos_nb = config->philos_nb;

	init_monitor(monitor, config);
	if (monitor->threads == NULL)
	{
		perror("init_monitor():malloc()");
		free_monitor(monitor, monitor->philos_nb);
		return (NULL);
	}
	return (monitor);
}
