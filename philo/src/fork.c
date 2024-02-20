/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:56:42 by aautin            #+#    #+#             */
/*   Updated: 2024/02/20 15:56:48 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	are_forks_free(t_bag *bag)
{
	char	status;

	if (*bag->i + 1 != *bag->philos_nb)
		pthread_mutex_lock(&bag->table->mutexs[(*bag->i)]);
	pthread_mutex_lock(&bag->table->mutexs[((*bag->i) + 1) % *bag->philos_nb]);
	if (*bag->i + 1 == *bag->philos_nb)
		pthread_mutex_lock(&bag->table->mutexs[(*bag->i)]);
	status = (bag->table->forks[*bag->i] == FREE
			&& bag->table->forks[((*bag->i) + 1) % *bag->philos_nb] == FREE);
	if (status == 1)
	{
		printlog(&bag->table->mutexs[*bag->philos_nb],
			bag->time->start, *bag->i, FORK);
		bag->table->forks[*bag->i] = TAKEN;
		bag->table->forks[((*bag->i) + 1) % *bag->philos_nb] = TAKEN;
	}
	if (*bag->i + 1 != *bag->philos_nb)
		pthread_mutex_unlock(&bag->table->mutexs[(*bag->i)]);
	pthread_mutex_unlock(&bag->table->mutexs[(*bag->i + 1) % *bag->philos_nb]);
	if (*bag->i + 1 == *bag->philos_nb)
		pthread_mutex_unlock(&bag->table->mutexs[(*bag->i)]);
	return (status);
}

void	free_forks(t_bag *bag)
{
	pthread_mutex_lock(&bag->table->mutexs[(*bag->i)]);
	bag->table->forks[*bag->i] = FREE;
	pthread_mutex_unlock(&bag->table->mutexs[(*bag->i)]);
	pthread_mutex_lock(&bag->table->mutexs[(*bag->i + 1) % *bag->philos_nb]);
	bag->table->forks[((*bag->i) + 1) % *bag->philos_nb] = FREE;
	pthread_mutex_unlock(&bag->table->mutexs[(*bag->i + 1) % *bag->philos_nb]);
}
