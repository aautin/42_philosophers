/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/07/13 18:30:07 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "config.h"
#include "monitor.h"

#define	FREE	0
#define	TAKEN	1

static void	init_sync_vars(t_sync_var **philos_status, t_sync_var **forks, t_config *config)
{
	int	i;

	i = 0;
	while (i < config->philos_nb)
	{
		forks[i] = malloc(sizeof(*forks[i]));
		if (forks[i] != NULL)
		{
			forks[i]->var = FREE;
			pthread_mutex_init(&forks[i]->mutex, NULL);
		}
		philos_status[i] = malloc(sizeof(*philos_status[i]));
		if (philos_status[i] != NULL)
		{
			philos_status[i]->var = config->meals_to_eat;
			pthread_mutex_init(&philos_status[i]->mutex, NULL);
		}
		i++;
	}
}

static void	init_philo(t_monitor *monitor, t_config *config, int i)
{
	monitor->philos[i]->time.die = config->time_to_die;
	monitor->philos[i]->time.eat = config->time_to_eat;
	monitor->philos[i]->time.sleep = config->time_to_sleep;
	monitor->philos[i]->philos_nb = config->philos_nb;
	monitor->philos[i]->index = i;

	monitor->philos[i]->printf = monitor->printf;
	monitor->philos[i]->status = monitor->philos_status[i];
	monitor->philos[i]->left_fork = monitor->forks[i];
	monitor->philos[i]->right_fork = monitor->forks[(i + config->philos_nb + 1) % config->philos_nb];
}

static void	init_monitor_philos(t_monitor *monitor, t_config *config)
{
	int	i;

	if (monitor->philos == NULL)
		return ;

	i = 0;
	while (i < config->philos_nb)
	{
		monitor->philos[i] = malloc(sizeof(*monitor->philos[i]));
		if (monitor->philos[i] != NULL)
			init_philo(monitor, config, i);
		i++;
	}
}

void	init_monitor(t_monitor *monitor, t_config *config)
{
	monitor->forks = malloc(config->philos_nb * sizeof(*monitor->forks));
	monitor->philos_status = malloc(config->philos_nb * sizeof(*monitor->philos_status));
	if (monitor->forks != NULL && monitor->philos_status != NULL)
		init_sync_vars(monitor->philos_status, monitor->forks, config);
	else
	{
		free(monitor->forks);
		free(monitor->philos_status);
		monitor->forks = NULL;
		monitor->philos_status = NULL;
	}

	monitor->printf = malloc(sizeof(*monitor->printf));

	monitor->philos = NULL;
	if (are_sync_vars_mallocated(monitor->philos_status, monitor->forks, config->philos_nb)
		&& monitor->printf != NULL)
	{
		monitor->philos = malloc(config->philos_nb * sizeof(*monitor->philos));	
		pthread_mutex_init(monitor->printf, NULL);
		init_monitor_philos(monitor, config);
	}

	monitor->threads = NULL;
	if (are_philos_mallocated(monitor->philos, config->philos_nb))
		monitor->threads = malloc(config->philos_nb * sizeof(*monitor->threads));
}
