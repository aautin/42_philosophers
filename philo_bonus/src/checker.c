/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:43:52 by aautin            #+#    #+#             */
/*   Updated: 2024/02/27 13:25:43 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	checker(t_bag *bag)
{
	while (is_time_to_die(bag->time, bag->sem.time) == 0)
	{
		usleep(200);
	}
}
