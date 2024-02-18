/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:12:20 by aautin            #+#    #+#             */
/*   Updated: 2024/02/17 21:28:47 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_time_to_die(t_bag *bag)
{
	t_time			current;
	unsigned int	milliseconds;

	gettimeofday(&current, NULL);
	milliseconds = 0;
	milliseconds += (current.tv_sec - bag->time->lastmeal.tv_sec)
		* 1000;
	milliseconds += (current.tv_usec - bag->time->lastmeal.tv_usec)
		/ 1000;
	if (milliseconds >= bag->time->to_die)
		return (1);
	return (0);
}

int	get_time_left(t_bag *bag)
{
	t_time	current;
	int		milliseconds;

	gettimeofday(&current, NULL);
	milliseconds = 0;
	milliseconds += (current.tv_sec - bag->time->lastmeal.tv_sec)
		* 1000;
	milliseconds += (current.tv_usec - bag->time->lastmeal.tv_usec)
		/ 1000;
	return (bag->time->to_die - milliseconds);
}
