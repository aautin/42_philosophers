/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bag.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:30:43 by aautin            #+#    #+#             */
/*   Updated: 2024/02/21 12:13:51 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
