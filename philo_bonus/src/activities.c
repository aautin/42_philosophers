/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:20:42 by aautin            #+#    #+#             */
/*   Updated: 2024/03/04 17:37:01 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	update_meals_nb(t_child *child)
{
	sem_wait(child->sem.child);
	if (child->nb.meals == 1)
		send_signal(child->sem.signal, 1);
	child->nb.meals = child->nb.meals - (child->nb.meals > 0);
	sem_post(child->sem.child);
}

void	eating(t_child *child)
{
	if (is_time_to_stop(child))
		pthread_exit(NULL);
	sem_wait(child->sem.forks);
	if (is_time_to_stop(child))
	{
		sem_post(child->sem.forks);
		pthread_exit(NULL);
	}
	printlog(child->sem.child, child->time.start, ft_atou(child->name), FORK);
	if (is_time_to_stop(child))
	{
		sem_post(child->sem.forks);
		pthread_exit(NULL);
	}
	gettimeofday(&child->time.lastmeal, NULL);
	printlog(child->sem.child, child->time.start, ft_atou(child->name), EATING);
	usleep(get_usleep_time(child->time, child->sem.child, EATING));
	sem_post(child->sem.forks);
	update_meals_nb(child);
	if (is_time_to_stop(child))
	{
		sem_post(child->sem.forks);
		pthread_exit(NULL);
	}
}

void	sleeping(t_child *child)
{	
	if (is_time_to_stop(child))
		pthread_exit(NULL);
	printlog(child->sem.child, child->time.start, ft_atou(child->name),
		SLEEPING);
	if (is_time_to_stop(child))
		pthread_exit(NULL);
	usleep(get_usleep_time(child->time, child->sem.child, SLEEPING));
	if (is_time_to_stop(child))
		pthread_exit(NULL);
}

void	thinking(t_child *child)
{
	if (is_time_to_stop(child))
		pthread_exit(NULL);
	printlog(child->sem.child, child->time.start, ft_atou(child->name),
		THINKING);
	if (is_time_to_stop(child))
		pthread_exit(NULL);
	if ((child->nb.philos % 2) == 1)
		usleep(get_thinking_sleep(child->time));
}
