/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:56:13 by aautin            #+#    #+#             */
/*   Updated: 2024/02/17 22:43:39 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	eat(t_bag *bag)
// {
// 	bag->config->forks[bag->i.i] = TAKEN;
// 	pthread_mutex_lock(&bag->config->mutexs[bag->i.i]);
// 	bag->config->forks[bag->i.right] = TAKEN;
// 	pthread_mutex_lock(&bag->config->mutexs[bag->i.right]);
// 	print_log(bag->config->start, bag->i.i, EATING);
// 	if (get_time_left(bag) + bag->config->to_eat >= bag->config->to_die)
// 	{
// 		kill_philo_during_action(bag, get_time_left(bag), EATING);
// 		pthread_mutex_unlock(&bag->config->mutexs[bag->i.i]);
// 		bag->config->forks[bag->i.i] = FREE;
// 		pthread_mutex_unlock(&bag->config->mutexs[bag->i.right]);
// 		bag->config->forks[bag->i.right] = FREE;
// 		pthread_exit((void *) bag);
// 	}
// 	else
// 		usleep(bag->config->to_eat * 1000);
// 	gettimeofday(&bag->config->meals[bag->i.i], NULL);
// 	pthread_mutex_unlock(&bag->config->mutexs[bag->i.i]);
// 	bag->config->forks[bag->i.i] = FREE;
// 	pthread_mutex_unlock(&bag->config->mutexs[bag->i.right]);
// 	bag->config->forks[bag->i.right] = FREE;
// }

static int	are_forks_free(t_bag *bag)
{
	char	status;

	pthread_mutex_lock(&bag->table->mutexs[(*bag->i)]);
	pthread_mutex_lock(&bag->table->mutexs[(*bag->i) + 1 % *bag->philos_nb]);
	if (bag->table->forks[*bag->i] == FREE
		&& bag->table->forks[(*bag->i + 1) % *bag->philos_nb] == FREE)
	{
		print_log(&bag->table->mutexs[*bag->philos_nb], bag->time->start, *bag->i, FORK);
		bag->table->forks[*bag->i] = TAKEN;
		bag->table->forks[(*bag->i + 1) % *bag->philos_nb] = TAKEN;
		status = TAKEN;
	}
	else
		status = FREE;
	pthread_mutex_unlock(&bag->table->mutexs[(*bag->i) + 1 % *bag->philos_nb]);
	pthread_mutex_unlock(&bag->table->mutexs[(*bag->i)]);
	return (status);
}

// static void	nap(t_bag *bag)
// {
// 	if (get_time_left(bag) + bag->config->to_sleep >= bag->config->to_die)
// 		kill_philo_during_action(bag, get_time_left(bag), SLEEPING);
// 	else
// 		usleep(bag->config->to_sleep * 1000);
// 	if (is_time_to_die(bag))
// 	{
// 		print_log(bag->config->start, bag->i.i, DIED);
// 		pthread_exit((void *) bag);
// 	}
// 	else if (are_forks_free(bag) == TAKEN)
// 		print_log(bag->config->start, bag->i.i, THINKING);
// }

void	*simulation(void *adress)
{
	t_bag	*bag;

	bag = (t_bag *) adress;
	gettimeofday(&bag->time->start, NULL);
	bag->time->lastmeal.tv_sec = bag->time->start.tv_sec;
	bag->time->lastmeal.tv_usec = bag->time->start.tv_usec;
	while (is_time_to_die(bag) == 0)
	{
		usleep(10000);
		if (are_forks_free(bag) == FREE)
		{
			eat(bag);
		}
	}
	print_log(&bag->table->mutexs[*bag->philos_nb], bag->time->start, *bag->i, DIED);
	pthread_exit(adress);
}
