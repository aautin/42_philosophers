/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:12:20 by aautin            #+#    #+#             */
/*   Updated: 2024/03/03 14:44:06 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_timers(t_table *table, t_timers *timers, char **argv)
{
	timers->to_die = ft_atou(argv[2]);
	timers->to_eat = ft_atou(argv[3]);
	timers->to_sleep = ft_atou(argv[4]);
	timers->start.tv_sec = table->start.tv_sec;
	timers->start.tv_usec = table->start.tv_usec;
}

int	is_time_to_die(t_bag *bag)
{
	t_time			current;
	long long int	milliseconds;

	gettimeofday(&current, NULL);
	milliseconds = 0;
	milliseconds += (current.tv_sec - bag->time->lastmeal.tv_sec)
		* 1000;
	milliseconds += (current.tv_usec - bag->time->lastmeal.tv_usec)
		/ 1000;
	if (milliseconds > bag->time->to_die)
		return (1);
	return (0);
}

long long int	get_time_left(t_bag *bag)
{
	t_time			current;
	long long int	milliseconds;

	gettimeofday(&current, NULL);
	milliseconds = 0;
	milliseconds += (current.tv_sec - bag->time->lastmeal.tv_sec)
		* 1000;
	milliseconds += (current.tv_usec - bag->time->lastmeal.tv_usec)
		/ 1000;
	return (bag->time->to_die - milliseconds);
}

void	kill_philo_during_action(t_bag *bag, int timeleft, char action)
{
	printlog(&bag->table->mutexs[*bag->philos_nb],
		bag->time->start, *bag->i, action);
	check_stop(bag);
	usleep(timeleft * 1000);
	check_stop(bag);
	change_finished_status(bag, -1);
	printlog(&bag->table->mutexs[*bag->philos_nb],
		bag->time->start, *bag->i, DIED);
}
