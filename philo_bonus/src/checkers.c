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

static void	send_stop_to_parent(unsigned int times, sem_t *stop)
{
	unsigned int	i;

	i = 0;
	while (i < times)
	{
		sem_post(stop);
		i++;
	}
}

void	thread_checker(t_bag *bag)
{
	while (is_time_to_die(bag->time, bag->sem->bag) == 0)
		usleep(40);
	printlog(bag->sem->bag, bag->time->start, bag->time->i, DIED);
	sem_wait(bag->sem->bag);
	bag->stop = 1;
	sem_post(bag->sem->bag);
	send_stop_to_parent(bag->philos_nb, bag->sem->stop);
}

void	parent_checker(unsigned int philos_nb, sem_t *stop)
{
	unsigned int	i;

	i = 0;
	while (i < philos_nb)
	{
		sem_wait(stop);
		i++;
	}
	printf("[!] Finish [!]\n");
}
