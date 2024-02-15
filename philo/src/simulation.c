/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:56:13 by aautin            #+#    #+#             */
/*   Updated: 2024/02/15 23:46:40 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_baggage *bag)
{
	int	i_left;
	int	i_right;

	if ((bag->i + 1) == bag->config->philos_nb)
	{
		i_left = bag->i;
		i_right = 0;
	}
	else
	{
		i_left = bag->i;
		i_right = bag->i + 1;
	}
	bag->config->forks[i_left] = 1;
	pthread_mutex_lock(&bag->config->mutexs[i_left]);
	bag->config->forks[i_right] = 1;
	pthread_mutex_lock(&bag->config->mutexs[i_right]);
	printf("Start[%d]\n", bag->i);
	usleep(bag->config->to_eat * 1000);
	printf("End\n");
	pthread_mutex_unlock(&bag->config->mutexs[i_left]);
	bag->config->forks[i_left] = 1;
	pthread_mutex_unlock(&bag->config->mutexs[i_right]);
	bag->config->forks[i_right] = 1;
}

static int	are_forks_free(t_baggage *bag)
{
	int	i_left;
	int	i_right;

	if ((bag->i + 1) == bag->config->philos_nb)
	{
		i_left = bag->i;
		i_right = 0;
	}
	else
	{
		i_left = bag->i;
		i_right = bag->i + 1;
	}
	if (bag->config->forks[i_left] == FREE && bag->config->forks[i_left] == FREE)
		return (FREE);
	return (TAKEN);
}

void	*simulation(void *adress)
{
	t_baggage	*bag;

	bag = (t_baggage *) adress;
	printf("Philos[%d]\n", bag->i);
	while (!is_time_to_die(bag))
	{
		if (are_forks_free(bag) == FREE)
			eat(bag);
	}
	pthread_exit(adress);
}
