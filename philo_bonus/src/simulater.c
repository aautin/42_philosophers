/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulater.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:44:07 by aautin            #+#    #+#             */
/*   Updated: 2024/02/26 14:53:14 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*simulation(void *arg)
{
	t_bag	*bag;

	bag = (t_bag *) arg;
	sem_close(bag->sem.fork);
	sem_close(bag->sem.time);
	pthread_exit(NULL);
}
