/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:56:13 by aautin            #+#    #+#             */
/*   Updated: 2024/02/16 18:27:05 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_baggage *bag)
{
	print_log(bag->config->start, bag->i.i, FORK);
	bag->config->forks[bag->i.i] = TAKEN;
	pthread_mutex_lock(&bag->config->mutexs[bag->i.i]);
	bag->config->forks[bag->i.right] = TAKEN;
	pthread_mutex_lock(&bag->config->mutexs[bag->i.right]);
	print_log(bag->config->start, bag->i.i, EATING);
	usleep(bag->config->to_eat * 1000);
	gettimeofday(&bag->config->meals[bag->i.i], NULL);
	pthread_mutex_unlock(&bag->config->mutexs[bag->i.i]);
	bag->config->forks[bag->i.i] = FREE;
	pthread_mutex_unlock(&bag->config->mutexs[bag->i.right]);
	bag->config->forks[bag->i.right] = FREE;
}

static int	are_forks_free(t_baggage *bag)
{
	if (bag->config->forks[bag->i.i] == FREE
		&& bag->config->forks[bag->i.right] == FREE)
		return (FREE);
	return (TAKEN);
}

static void	nap(t_baggage *bag)
{
	print_log(bag->config->start, bag->i.i, SLEEPING);
	usleep(bag->config->to_sleep * 1000);
	if (are_forks_free(bag) == TAKEN)
		print_log(bag->config->start, bag->i.i, THINKING);
}

void	*simulation(void *adress)
{
	t_baggage	*bag;

	bag = (t_baggage *) adress;
	while (!is_time_to_die(bag))
	{
		if (are_forks_free(bag) == FREE)
		{
			eat(bag);
			nap(bag);
		}
	}
	print_log(bag->config->start, bag->i.i, DIED);
	pthread_exit(adress);
}
