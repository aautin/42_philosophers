/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:51:19 by aautin            #+#    #+#             */
/*   Updated: 2024/03/04 12:49:09 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_child(t_bag *bag)
{
	sem_unlink(bag->name);
	sem_close(bag->sem.child);
	free(bag->name);
}

static int	init_child_struct(t_bag *bag, t_parent *parent, char **argv,
	unsigned int i)
{
	bag->name = ft_utoa(i);
	if (bag->name == NULL)
		return (1);
	bag->sem.child = sem_open(bag->name, O_CREAT | O_EXCL, 777, 1);
	if (bag->sem.child == NULL)
		return (free(bag->name), 1);
	bag->sem.forks = parent->forks;
	bag->sem.signal = parent->signal;
	bag->time.start.tv_sec = parent->start.tv_sec;
	bag->time.start.tv_usec = parent->start.tv_usec;
	set_timers(&bag->time, argv);
	bag->nb.stop = 0;
	bag->nb.philos = parent->philos_nb;
	if (argv[5])
		bag->nb.meals = ft_atou(argv[5]);
	else
		bag->nb.meals = -1;
	return (0);
}

int	child_process(t_parent *parent, char **argv, unsigned int i)
{
	t_bag	bag;

	if (init_child_struct(&bag, parent, argv, i) == 1)
	{
		send_signal(bag.sem.child, bag.nb.philos);
		return (close_parent(parent), EXIT_FAILURE);
	}
	send_signal(bag.sem.signal, bag.nb.philos);
	return (close_child(&bag), close_parent(parent), EXIT_SUCCESS);
}
