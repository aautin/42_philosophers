/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:12:38 by aautin            #+#    #+#             */
/*   Updated: 2024/02/21 12:12:41 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_finished_string(t_table *table, unsigned short philos_nb)
{
	unsigned int	i;

	i = 0;
	while (i < philos_nb)
	{
		table->finished[i] = 0;
		i++;
	}
}

int	set_table(t_table *table, unsigned short philos_nb)
{
	int	i;

	table->forks = (char *)malloc(philos_nb * sizeof(char));
	table->finished = (char *)malloc(philos_nb * sizeof(char));
	table->mutexs = (t_mutex *)malloc((philos_nb + 2) * sizeof(t_mutex));
	table->philos = (t_thread *)malloc(philos_nb * sizeof(t_thread));
	if (!table->forks || !table->mutexs || !table->philos || !table->finished)
	{
		if (table->forks)
			free(table->forks);
		if (table->finished)
			free(table->finished);
		if (table->mutexs)
			free(table->mutexs);
		if (table->philos)
			free(table->philos);
		return (printf("malloc issue\n"), 1);
	}
	i = 0;
	while (i < philos_nb)
		table->forks[i++] = FREE;
	i = 0;
	while (i < philos_nb + 2)
		pthread_mutex_init(&table->mutexs[i++], NULL);
	return (set_finished_string(table, philos_nb), 0);
}

void	free_table(t_table *table, unsigned short philos_nb)
{
	int	i;

	i = 0;
	while (i < philos_nb + 2)
		pthread_mutex_destroy(&table->mutexs[i++]);
	free(table->forks);
	free(table->finished);
	free(table->mutexs);
	free(table->philos);
}