/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:30:43 by aautin            #+#    #+#             */
/*   Updated: 2024/02/15 23:43:27 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_times(t_config *config, char **argv)
{
	config->philos_nb = ft_atoi(argv[1]);
	config->to_die = ft_atoi(argv[2]);
	config->to_eat = ft_atoi(argv[3]);
	config->to_sleep = ft_atoi(argv[4]);
	printf("nb_of_philosophers[%d]\n", config->philos_nb);
	printf("time_to_die[%d]\n", config->to_die);
	printf("time_to_eat[%d]\n", config->to_eat);
	printf("time_to_sleep[%d]\n", config->to_sleep);
}

int	set_table(t_config *config)
{
	int	i;

	config->forks = (char *)malloc(config->philos_nb * sizeof(char));
	config->mutexs = (t_mutex *)malloc(config->philos_nb * sizeof(t_mutex));
	config->philos = (t_thread *)malloc(config->philos_nb * sizeof(t_thread));
	config->meals = (t_time *)malloc(config->philos_nb * sizeof(t_time));
	if (!config->forks || !config->mutexs || !config->philos || !config->meals)
	{
		if (config->forks)
			free(config->forks);
		if (config->mutexs)
			free(config->mutexs);
		if (config->philos)
			free(config->philos);
		if (config->meals)
			free(config->meals);
		return (printf("malloc issue\n"), 1);
	}
	i = 0;
	while (i < config->philos_nb)
	{
		config->forks[i] = FREE;
		pthread_mutex_init(&config->mutexs[i++], NULL);
	}
	return (0);
}

void	free_config(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->philos_nb)
		pthread_mutex_destroy(&config->mutexs[i++]);
	free(config->philos);
	free(config->mutexs);
	free(config->meals);
	free(config->forks);
}
