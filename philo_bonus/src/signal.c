/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:07:49 by aautin            #+#    #+#             */
/*   Updated: 2024/03/04 17:23:50 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	send_signal(sem_t *signal, unsigned int signals_nb)
{
	unsigned int	i;

	i = 0;
	while (i < signals_nb)
	{
		sem_post(signal);
		i++;
	}
}

void	wait_signal(sem_t *signal, unsigned int signals_nb)
{
	unsigned int	i;

	i = 0;
	while (i < signals_nb)
	{
		sem_wait(signal);
		i++;
	}
}
