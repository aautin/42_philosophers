/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:51:19 by aautin            #+#    #+#             */
/*   Updated: 2024/03/04 17:47:02 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_child(t_child *child)
{
	sem_unlink(child->name);
	sem_close(child->sem.child);
	free(child->name);
}

static int	init_child_struct(t_child *child, t_parent *parent, char **argv,
	unsigned int i)
{
	child->name = ft_utoa(i);
	if (child->name == NULL)
		return (1);
	child->sem.child = sem_open(child->name, O_CREAT | O_EXCL, 777, 1);
	if (child->sem.child == NULL)
		return (free(child->name), 1);
	child->sem.forks = parent->forks;
	child->sem.signal = parent->signal;
	child->sem.kill = parent->kill;
	child->time.start.tv_sec = parent->start.tv_sec;
	child->time.start.tv_usec = parent->start.tv_usec;
	set_timers(&child->time, argv);
	child->nb.stop = 0;
	child->nb.philos = parent->philos_nb;
	if (argv[5])
		child->nb.meals = ft_atou(argv[5]);
	else
		child->nb.meals = -1;
	return (0);
}

int	child_process(t_parent *parent, char **argv, unsigned int i)
{
	t_child		child;
	pthread_t	th[2];

	if (init_child_struct(&child, parent, argv, i) == 1)
	{
		send_signal(child.sem.child, child.nb.philos);
		return (close_parent(parent), EXIT_FAILURE);
	}
	if (pthread_create(&th[0], NULL, &intern_checking, &child) == -1)
	{
		printf("pthread_create() issue\n");
		send_signal(child.sem.signal, child.nb.philos);
		return (close_child(&child), close_parent(parent), EXIT_FAILURE);
	}
	if (pthread_create(&th[1], NULL, &simulating, &child) == -1)
	{
		printf("pthread_create() issue\n");
		send_signal(child.sem.signal, child.nb.philos);
		sem_wait(child.sem.child);
		child.nb.stop = 1;
		sem_post(child.sem.child);
		if (pthread_join(th[0], NULL) == -1)
			printf("pthread_join() issue\n");
		return (close_child(&child), close_parent(parent), EXIT_FAILURE);
	}
	extern_checking(&child);
	if (pthread_join(th[0], NULL) == -1 || pthread_join(th[1], NULL) == -1)
		printf("pthread_create() issue\n");
	printf("[%s] finished\n", child.name);
	return (close_child(&child), close_parent(parent), EXIT_SUCCESS);
}
