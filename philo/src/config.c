/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:30:43 by aautin            #+#    #+#             */
/*   Updated: 2024/02/17 22:25:02 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	are_argvs_correct(int argc, char *argv[])
{
	unsigned short	philos_nb;
	unsigned int	to_die;
	unsigned int	to_eat;
	unsigned int	to_sleep;
	unsigned int	meals_left;

	philos_nb = ft_atou(argv[1]);
	to_die = ft_atou(argv[2]);
	to_eat = ft_atou(argv[3]);
	to_sleep = ft_atou(argv[4]);
	if (argc == 6)
	{
		meals_left = ft_atou(argv[5]);
		if (philos_nb == 0 || to_die == 0 || to_eat == 0 || to_sleep == 0
			|| meals_left == 0)
			return (printf("Each argument must be strictely positive nbr\n"), 0);
	}
	else
	{
		if (philos_nb == 0 || to_die == 0 || to_eat == 0 || to_sleep == 0)
			return (printf("Each argument must be strictely positive nbr\n"), 0);
	}
	return (1);
}

void	set_timers(t_timers *timers, char **argv)
{
	timers->to_die = ft_atou(argv[2]);
	timers->to_eat = ft_atou(argv[3]);
	timers->to_sleep = ft_atou(argv[4]);
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
		if (table->finished)
			free(table->finished);
		if (table->forks)
			free(table->forks);
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
	return (0);
}

void	free_table(t_table *table, unsigned short philos_nb)
{
	int	i;

	i = 0;
	while (i < philos_nb + 2)
		pthread_mutex_destroy(&table->mutexs[i++]);
	free(table->philos);
	free(table->mutexs);
	free(table->forks);
}

void	free_bag(t_bag *bag)
{
	if (bag->philos_nb)
		free(bag->philos_nb);
	if (bag->i)
		free(bag->i);
	if (bag->time)
		free(bag->time);
	free(bag);
}
