/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:56:13 by aautin            #+#    #+#             */
/*   Updated: 2024/02/18 19:56:47 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	are_forks_free(t_bag *bag)
{
	char	status;

	if (*bag->i + 1 != *bag->philos_nb)
		pthread_mutex_lock(&bag->table->mutexs[(*bag->i)]);
	pthread_mutex_lock(&bag->table->mutexs[((*bag->i) + 1) % *bag->philos_nb]);
	if (*bag->i + 1 == *bag->philos_nb)
		pthread_mutex_lock(&bag->table->mutexs[(*bag->i)]);
	status = (bag->table->forks[*bag->i] == FREE
			&& bag->table->forks[((*bag->i) + 1) % *bag->philos_nb] == FREE);
	if (status == 1)
	{
		printlog(&bag->table->mutexs[*bag->philos_nb],
			bag->time->start, *bag->i, FORK);
		bag->table->forks[*bag->i] = TAKEN;
		bag->table->forks[((*bag->i) + 1) % *bag->philos_nb] = TAKEN;
	}
	if (*bag->i + 1 != *bag->philos_nb)
		pthread_mutex_unlock(&bag->table->mutexs[(*bag->i)]);
	pthread_mutex_unlock(&bag->table->mutexs[(*bag->i + 1) % *bag->philos_nb]);
	if (*bag->i + 1 == *bag->philos_nb)
		pthread_mutex_unlock(&bag->table->mutexs[(*bag->i)]);
	return (status);
}

static void	free_forks(t_bag *bag)
{
	pthread_mutex_lock(&bag->table->mutexs[(*bag->i)]);
	bag->table->forks[*bag->i] = FREE;
	pthread_mutex_unlock(&bag->table->mutexs[(*bag->i)]);
	pthread_mutex_lock(&bag->table->mutexs[(*bag->i + 1) % *bag->philos_nb]);
	bag->table->forks[((*bag->i) + 1) % *bag->philos_nb] = FREE;
	pthread_mutex_unlock(&bag->table->mutexs[(*bag->i + 1) % *bag->philos_nb]);
}

static void	eat(t_bag *bag)
{
	gettimeofday(&bag->time->lastmeal, NULL);
	check_stop(bag);
	if (get_time_left(bag) < bag->time->to_eat)
	{
		check_stop(bag);
		kill_philo_during_action(bag, get_time_left(bag), EATING);
		free_forks(bag);
		pthread_exit((void *) bag);
	}
	else
	{
		check_stop(bag);
		printlog(&bag->table->mutexs[*bag->philos_nb],
			bag->time->start, *bag->i, EATING);
		usleep(bag->time->to_eat * 1000);
		if (*bag->meals_left == 1)
			change_finished_status(bag, 1);
		*bag->meals_left -= (*bag->meals_left > 0);
		free_forks(bag);
		check_stop(bag);
	}
}

static void	nap(t_bag *bag)
{
	if (get_time_left(bag) < bag->time->to_sleep)
	{
		check_stop(bag);
		kill_philo_during_action(bag, get_time_left(bag), SLEEPING);
		pthread_exit((void *) bag);
	}
	else
	{
		check_stop(bag);
		printlog(&bag->table->mutexs[*bag->philos_nb],
			bag->time->start, *bag->i, SLEEPING);
		usleep(bag->time->to_sleep * 1000);
	}
	if (are_forks_free(bag) == 0)
		printlog(&bag->table->mutexs[*bag->philos_nb],
			bag->time->start, *bag->i, THINKING);
	else
	{
		eat(bag);
		nap(bag);
		check_stop(bag);
	}
}

void	*simulation(void *adress)
{
	t_bag	*bag;

	bag = (t_bag *) adress;
	change_finished_status(bag, 0);
	gettimeofday(&bag->time->start, NULL);
	bag->time->lastmeal.tv_sec = bag->time->start.tv_sec;
	bag->time->lastmeal.tv_usec = bag->time->start.tv_usec;
	while (is_time_to_die(bag) == 0)
	{
		check_stop(bag);
		if (are_forks_free(bag) == 1)
		{
			eat(bag);
			nap(bag);
			check_stop(bag);
		}
	}
	printlog(&bag->table->mutexs[*bag->philos_nb],
		bag->time->start, *bag->i, DIED);
	change_finished_status(bag, -1);
	pthread_exit(adress);
}
