/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:56:13 by aautin            #+#    #+#             */
/*   Updated: 2024/02/21 13:08:17 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_bag *bag)
{
	gettimeofday(&bag->time->lastmeal, NULL);
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
	check_stop(bag);
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
	check_stop(bag);
	if (are_forks_free(bag) == 0)
		printlog(&bag->table->mutexs[*bag->philos_nb],
			bag->time->start, *bag->i, THINKING);
	else
	{
		eat(bag);
		nap(bag);
	}
}

void	*simulation(void *adress)
{
	t_bag	*bag;

	bag = (t_bag *) adress;
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
		}
	}
	check_stop(bag);
	printlog(&bag->table->mutexs[*bag->philos_nb],
		bag->time->start, *bag->i, DIED);
	change_finished_status(bag, -1);
	pthread_exit(adress);
}
