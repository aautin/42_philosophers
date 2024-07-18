/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/07/18 20:23:42 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "common.h"
#include "config.h"
#include "philo.h"
#include "monitor.h"

static void	init_forks(t_sync_var **forks, t_config *config)
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
		i++;
	}
}

static void	init_philo(t_monitor *monitor, t_config *config, int i)
{
	monitor->philos[i]->times.die = config->time_to_die;
	monitor->philos[i]->times.eat = config->time_to_eat;
	monitor->philos[i]->times.sleep = config->time_to_sleep;
	monitor->philos[i]->meals_to_eat = config->meals_to_eat;
	monitor->philos[i]->philos_nb = config->philos_nb;
	monitor->philos[i]->index = i;
	monitor->philos[i]->print = monitor->print;
	monitor->philos[i]->sim_status = monitor->sim_status;
	monitor->philos[i]->left_fork = monitor->forks[i];
	monitor->philos[i]->right_fork = monitor->forks[(i + config->philos_nb + 1)
		% config->philos_nb];
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
	monitor->sim_status = malloc(sizeof(*monitor->sim_status));
	if (monitor->forks != NULL && monitor->sim_status != NULL)
		init_forks(monitor->forks, config);
	else
	{
		free(monitor->forks);
		free(monitor->sim_status);
		monitor->forks = NULL;
		monitor->sim_status = NULL;
	}
	monitor->print = malloc(sizeof(*monitor->print));
	monitor->philos = NULL;
	if (are_forks_mallocated(monitor->forks, config->philos_nb)
			&& monitor->print != NULL)
	{
		monitor->philos = malloc(config->philos_nb * sizeof(*monitor->philos));
		pthread_mutex_init(monitor->print, NULL);
		pthread_mutex_init(&monitor->sim_status->mutex, NULL);
		monitor->sim_status->var = WAIT;
		init_monitor_philos(monitor, config);
	}
	monitor->threads = NULL;
	if (are_philos_mallocated(monitor->philos, config->philos_nb))
		monitor->threads = malloc(config->philos_nb * sizeof(pthread_t));
}
