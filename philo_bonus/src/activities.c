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
	sem_wait(child->sem.child);
	gettimeofday(&child->time.lastmeal, NULL);
	sem_post(child->sem.child);
	printlog(child->sem.child, child->time.start, ft_atou(child->name), EATING);
	usleep(get_usleep_time(child->time, child->sem.child, EATING));
	if (is_time_to_stop(child))
	{
		sem_post(child->sem.forks);
		pthread_exit(NULL);
	}
	sem_post(child->sem.forks);
}

void	sleeping(t_child *child)
{	
	if (is_time_to_stop(child))
		pthread_exit(NULL);
	printlog(child->sem.child, child->time.start, ft_atou(child->name),
		SLEEPING);
	return ;
}

void	thinking(t_child *child)
{
	(void) child;
	return ;
}
