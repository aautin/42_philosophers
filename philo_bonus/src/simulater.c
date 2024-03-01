/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulater.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:44:07 by aautin            #+#    #+#             */
/*   Updated: 2024/02/28 18:40:02 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	eat(t_bag *bag, sem_t *forks)
{
	int	buff;

	sem_wait(forks);
	if (is_time_to_stop(bag, bag->sem->bag) == 1)
	{
		sem_post(forks);
		pthread_exit(bag);
	}
	printlog(bag->sem->bag, bag->time->start, bag->time->i, FORK);
	if (is_time_to_stop(bag, bag->sem->bag) == 1)
	{
		sem_post(forks);
		pthread_exit(bag);
	}
	printlog(bag->sem->bag, bag->time->start, bag->time->i, EATING);
	gettimeofday(&bag->time->lastmeal, NULL);
	usleep(get_usleep_time(bag->time, bag->time->to_eat, bag->sem->bag));
	if (bag->meals_left == 1)
	{
		sem_post(bag->sem->stop);
		sem_getvalue(bag->sem->stop, &buff);
		printf("[%d] finished to eat (%d)\n", bag->time->i, buff);
	}
	bag->meals_left = bag->meals_left - (bag->meals_left > 0);
	sem_post(forks);
}

static void	nap(t_bag *bag)
{
	if (is_time_to_stop(bag, bag->sem->bag) == 1)
		pthread_exit(bag);
	printlog(bag->sem->bag, bag->time->start, bag->time->i, SLEEPING);
	usleep(get_usleep_time(bag->time, bag->time->to_sleep, bag->sem->bag));
	if (is_time_to_stop(bag, bag->sem->bag) == 1)
		pthread_exit(bag);
	printlog(bag->sem->bag, bag->time->start, bag->time->i, THINKING);
}

void	*simulation(void *arg)
{
	t_bag	*bag;

	bag = (t_bag *) arg;
	printf("must_eat:%d\n", bag->meals_left);
	while (is_time_to_stop(bag, bag->sem->bag) == 0)
	{
		eat(bag, bag->sem->forks);
		nap(bag);
	}
	pthread_exit(bag);
}
