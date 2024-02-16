/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:12:20 by aautin            #+#    #+#             */
/*   Updated: 2024/02/16 16:25:05 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_time_to_die(t_baggage *bag)
{
	t_time	current;
	int		milliseconds;

	gettimeofday(&current, NULL);
	milliseconds = 0;
	milliseconds += (current.tv_sec - bag->config->meals[bag->i.i].tv_sec)
		* 1000;
	milliseconds += (current.tv_usec - bag->config->meals[bag->i.i].tv_usec)
		/ 1000;
	if (milliseconds >= bag->config->to_die)
		return (1);
	return (0);
}
