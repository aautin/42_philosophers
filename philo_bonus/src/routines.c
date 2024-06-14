/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:55:02 by aautin            #+#    #+#             */
/*   Updated: 2024/06/14 17:46:11 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	extern_checking(t_child *child, pthread_t *th)
{
	sem_wait(child->sem.kill);
	sem_wait(child->sem.child);
	child->nb.stop = 1;
	sem_post(child->sem.child);
	if (pthread_join(th[0], NULL) == -1)
		printf("pthread_create() issue\n");
	if (pthread_join(th[1], NULL) == -1)
		printf("pthread_create() issue\n");
}

void	*intern_checking(void *arg)
{
	t_child	*child;

	child = (t_child *) arg;
	while (is_time_to_die(child) == 0)
	{
		if (is_time_to_stop(child) == 1)
			pthread_exit(NULL);
		usleep(1000);
	}
	send_signal(child->sem.signal, child->nb.philos);
	sem_wait(child->sem.child);
	child->nb.stop = 1;
	sem_post(child->sem.child);
	printlog(child->sem.child, child->time.start, ft_atou(child->name), DIED);
	pthread_exit(NULL);
}

void	*simulating(void *arg)
{
	t_child	*child;

	child = (t_child *) arg;
	if (child->nb.philos == 1)
		pthread_exit(NULL);
	sem_wait(child->sem.child);
	if (ft_atou(child->name) % 2 == 1)
		usleep((child->time.to_eat * 1000) - 1);
	sem_post(child->sem.child);
	if (is_time_to_stop(child))
		pthread_exit(NULL);
	while (is_time_to_stop(child) == 0)
	{
		eating(child);
		sleeping(child);
		thinking(child);
	}
	pthread_exit(NULL);
}
