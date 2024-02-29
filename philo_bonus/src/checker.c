/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:43:52 by aautin            #+#    #+#             */
/*   Updated: 2024/02/28 18:28:33 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	checker(t_bag *bag)
{
	while (is_time_to_die(bag->time, bag->sem->bag) == 0)
		usleep(40);
	printlog(bag->sem->bag, bag->time->start, bag->time->i, DIED);
	sem_wait(bag->sem->bag);
	bag->stop = 1;
	sem_post(bag->sem->bag);
}
