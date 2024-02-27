/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulater.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:44:07 by aautin            #+#    #+#             */
/*   Updated: 2024/02/27 13:25:18 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*simulation(void *arg)
{
	t_bag	*bag;

	bag = (t_bag *) arg;
	while (is_time_to_die(bag->time, bag->sem.time) == 0)
	{
		usleep(200);
	}
	pthread_exit(NULL);
}
