/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/07/20 19:48:03 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "config.h"
#include "monitor.h"
#include "utils.h"

int	are_forks_mallocated(t_sync_var **forks, int philos_nb)
{
	int	i;

	if (forks == NULL)
		return (FALSE);
	i = 0;
	while (i < philos_nb)
	{
		if (forks[i] == NULL)
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
	free(monitor->sim_status);
	free(monitor->print);
	free(monitor);
}

t_monitor	*get_monitor(t_config *config)
{
	t_monitor	*monitor;

	monitor = malloc(sizeof(*monitor));
	if (monitor == NULL)
		return (NULL);
	monitor->philos_nb = config->philos_nb;
	monitor->meals_to_eat = config->meals_to_eat;
	init_monitor(monitor, config);
	if (monitor->threads == NULL)
	{
		perror("init_monitor():malloc()");
		free_monitor(monitor, monitor->philos_nb);
		return (NULL);
	}
	return (monitor);
}

void	monitoring(t_monitor *monitor)
{
	while (42)
	{
		pthread_mutex_lock(&monitor->sim_status->mutex);
		if (monitor->sim_status->var == EXIT)
		{
			pthread_mutex_unlock(&monitor->sim_status->mutex);
			break ;
		}
		pthread_mutex_unlock(&monitor->sim_status->mutex);
		usleep(1000);
	}
}
