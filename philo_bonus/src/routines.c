/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:55:02 by aautin            #+#    #+#             */
/*   Updated: 2024/03/04 17:31:10 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	extern_checking(t_child *child)
{
	sem_wait(child->sem.kill);
	sem_wait(child->sem.child);
	child->nb.stop = 1;
	sem_post(child->sem.child);
	printf("extern[%s] finished\n", child->name);
}

void	*intern_checking(void *arg)
{
	t_child	*child;

	child = (t_child *) arg;
	while (is_time_to_die(child) == 0)
	{
		if (is_time_to_stop(child) == 1)
			pthread_exit(NULL);
		usleep(10);
	}
	send_signal(child->sem.signal, child->nb.philos);
	sem_wait(child->sem.child);
	child->nb.stop = 1;
	sem_post(child->sem.child);
	printf("intern[%s] finished\n", child->name);
	pthread_exit(NULL);
}

void	*simulating(void *arg)
{
	t_child	*child;

	child = (t_child *) arg;
	while (is_time_to_stop(child) == 0)
	{
		eating(child);
		sleeping(child);
		thinking(child);
	}
	printf("simul[%s] finished\n", child->name);
	pthread_exit(NULL);
}
