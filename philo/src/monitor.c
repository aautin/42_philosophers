/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/07/17 16:55:14 by aautin           ###   ########.fr       */
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
	int	i;
	int	still_meals_to_be_eaten;

	i = monitor->philos_nb;
	while (i == monitor->philos_nb)
	{
		still_meals_to_be_eaten = FALSE;
		i = 0;
		while (i < monitor->philos_nb)
		{
			pthread_mutex_lock(&monitor->philos_status[i]->mutex);
			if (monitor->philos_status[i]->var == DEAD)
			{
				pthread_mutex_unlock(&monitor->philos_status[i]->mutex);
				break ;
			}
			if (monitor->philos_status[i]->var > 0)
				still_meals_to_be_eaten = TRUE;
			pthread_mutex_unlock(&monitor->philos_status[i]->mutex);
			i++;
		}
		if (monitor->meals_to_eat != NO_MEALS_LIMIT
				&& still_meals_to_be_eaten == FALSE)
			break ;
	}
}
