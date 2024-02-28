/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulater.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:44:07 by aautin            #+#    #+#             */
/*   Updated: 2024/02/28 18:40:02 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// static void	eat(t_bag *bag, sem_t *forks)
// {
// 	sem_wait(forks);
// 	printlog(bag->sem->bag, bag->time->start, bag->time->i, FORK);
// 	sem_wait(forks);
// 	printlog(bag->sem->bag, bag->time->start, bag->time->i, FORK);
	
// }

void	*simulation(void *arg)
{
	t_bag	*bag;

	bag = (t_bag *) arg;
	while (is_time_to_stop(bag, bag->sem->bag) == 0)
	{
		// eat();
		// nap();
	}
	pthread_exit(NULL);
}
