/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:12:41 by aautin            #+#    #+#             */
/*   Updated: 2024/02/28 18:04:44 by aautin           ###   ########.fr       */
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

char	is_time_to_die(t_times *time, sem_t *bag)
{
	t_time			current;
	unsigned int	time_spent;
	char			must_die;

	gettimeofday(&current, NULL);
	sem_wait(bag);
	time_spent = (current.tv_sec * 1000) - (time->lastmeal.tv_sec * 1000);
	time_spent += (current.tv_usec / 1000) - (time->lastmeal.tv_usec / 1000);
	must_die = (time_spent >= time->to_die);
	sem_post(bag);
	return (must_die);
}

char	is_time_to_stop(t_bag *bag, sem_t *sem_bag)
{
	char	die_flag;

	sem_wait(sem_bag);
	die_flag = bag->stop;
	sem_post(sem_bag);
	return (die_flag);
}
