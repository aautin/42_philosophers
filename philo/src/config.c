/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:30:43 by aautin            #+#    #+#             */
/*   Updated: 2024/02/15 16:58:42 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_times(t_config *config, char **argv)
{
	config->philos_nb = ft_atoi(argv[1]);
	config->to_die = ft_atoi(argv[2]);
	config->to_eat = ft_atoi(argv[3]);
	config->to_sleep = ft_atoi(argv[4]);
	gettimeofday(&config->start, NULL);
	printf("nb_of_philosophers[%d]\n", config->philos_nb);
	printf("time_to_die[%d]\n", config->to_die);
	printf("time_to_eat[%d]\n", config->to_eat);
	printf("time_to_sleep[%d]\n", config->to_sleep);
	printf("start_local_time[%ld][%ld]\n",
		get_current_time(config).tv_sec, get_current_time(config).tv_usec);
}

int	set_forks(t_config *config)
{
	int	i;

	config->forks = (char *)malloc(config->philos_nb * sizeof(char));
	if (config->forks == NULL)
		return (printf("malloc issue\n"), 1);
	config->mutexs = (t_mutex *)malloc(config->philos_nb * sizeof(t_mutex));
	if (config->mutexs == NULL)
		return (free(config->forks), printf("malloc issue\n"), 1);
	config->philos = (t_thread *)malloc(config->philos_nb * sizeof(t_thread));
	if (config->philos == NULL)
	{
		free(config->forks);
		free(config->mutexs);
		return (printf("malloc issue\n"), 1);
	}
	i = 0;
	while (i < config->philos_nb)
	{
		config->forks[i] = 0;
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
	free(config->forks);
	free(config->mutexs);
	free(config->philos);
}