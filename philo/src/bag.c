/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bag.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:30:43 by aautin            #+#    #+#             */
/*   Updated: 2024/02/21 12:39:49 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc_bag_components(t_bag *bag)
{
	bag->time = (t_timers *)malloc(sizeof(t_timers));
	bag->i = (unsigned short *)malloc(sizeof(unsigned short));
	bag->philos_nb = (unsigned short *)malloc(sizeof(unsigned short));
	bag->meals_left = (int *)malloc(sizeof(int));
	if (!bag->time || !bag->i || !bag->philos_nb || !bag->meals_left)
		return (1);
	else
		return (0);
}

void	free_bag(t_bag *bag)
{
	if (bag->philos_nb)
		free(bag->philos_nb);
	if (bag->i)
		free(bag->i);
	if (bag->time)
		free(bag->time);
	if (bag->meals_left)
		free(bag->meals_left);
	free(bag);
}
