/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:12:41 by aautin            #+#    #+#             */
/*   Updated: 2024/03/04 17:01:12 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_timers(t_times *timers, char **argv)
{
	timers->lastmeal.tv_sec = timers->start.tv_sec;
	timers->lastmeal.tv_usec = timers->start.tv_usec;
	timers->to_die = ft_atou(argv[2]);
	timers->to_eat = ft_atou(argv[3]);
	timers->to_sleep = ft_atou(argv[4]);
}

int	is_time_to_stop(t_child *child)
{
	char	stop;

	sem_wait(child->sem.child);
	stop = child->nb.stop;
	sem_post(child->sem.child);
	return (stop);
}

int	is_time_to_die(t_child *child)
{
	char			die;
	t_time			current;
	unsigned int	time_spent;

	gettimeofday(&current, NULL);
	sem_wait(child->sem.child);
	time_spent = current.tv_sec * 1000 - child->time.lastmeal.tv_sec * 1000;
	time_spent += current.tv_usec / 1000 - child->time.lastmeal.tv_usec / 1000;
	if (time_spent < child->time.to_die)
		die = 0;
	else
		die = 1;
	sem_post(child->sem.child);
	return (die);
}

unsigned int	get_usleep_time(t_times time, sem_t *sem, char action)
{
	t_time			current;
	unsigned int	time_spent;

	gettimeofday(&current, NULL);
	sem_wait(sem);
	time_spent = current.tv_sec * 1000 - time.lastmeal.tv_sec * 1000;
	time_spent += current.tv_usec / 1000 - time.lastmeal.tv_usec / 1000;
	if (action == EATING)
	{
		if (time.to_die - time_spent < time.to_eat)
			return (sem_post(sem), (time.to_die - time_spent) * 1000);
		else
			return (sem_post(sem), time.to_eat * 1000);
	}
	if (action == SLEEPING)
	{
		if (time.to_die - time_spent < time.to_sleep)
			return (sem_post(sem), (time.to_die - time_spent) * 1000);
		else
			return (sem_post(sem), time.to_sleep * 1000);
	}
	return (sem_post(sem), time.to_die * 1000);
}
