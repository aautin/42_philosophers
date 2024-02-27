/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:12:41 by aautin            #+#    #+#             */
/*   Updated: 2024/02/27 12:10:57 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_timers(t_times *timers, t_time start, char **argv)
{
	timers->start.tv_sec = start.tv_sec;
	timers->start.tv_usec = start.tv_usec;
	timers->lastmeal.tv_sec = timers->start.tv_sec;
	timers->lastmeal.tv_usec = timers->start.tv_usec;
	timers->to_die = ft_atou(argv[2]);
	timers->to_eat = ft_atou(argv[3]);
	timers->to_sleep = ft_atou(argv[4]);
}

char	is_time_to_die(t_times *time, sem_t *sem_time)
{
	t_time			current;
	unsigned int	time_spent;
	char			must_die;

	gettimeofday(&current, NULL);
	sem_wait(sem_time);
	time_spent = current.tv_sec * 1000 - time->lastmeal.tv_sec * 1000;
	time_spent = current.tv_usec / 1000 - time->lastmeal.tv_usec / 1000;
	must_die = time_spent > time->to_die;
	sem_post(sem_time);
	if (must_die)
		return (1);
	else
		return (0);
}
