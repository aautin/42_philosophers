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

	sem_wait(bag);
	gettimeofday(&current, NULL);
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

unsigned int	get_usleep_time(t_times *time, unsigned int action, sem_t *sem)
{
	t_time			current;
	unsigned int	time_since_lastmeal;
	unsigned int	time_until_die;

	sem_wait(sem);
	gettimeofday(&current, NULL);
	time_since_lastmeal = (current.tv_sec * 1000) - (time->lastmeal.tv_sec * 1000);
	time_since_lastmeal += (current.tv_usec / 1000) - (time->lastmeal.tv_usec / 1000);
	time_until_die = time->to_die - time_since_lastmeal;
	sem_post(sem);
	if (time_until_die > action)
		return (action * 1000);
	else
		return (time_until_die * 1000);
}
