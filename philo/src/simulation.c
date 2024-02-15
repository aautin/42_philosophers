/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:56:13 by aautin            #+#    #+#             */
/*   Updated: 2024/02/15 20:28:50 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*simulation(void *adress)
{
	t_baggage	*bag;

	bag = (t_baggage *) adress;
	printf("philos[%d]\n", bag->i);
	pthread_mutex_lock(&bag->config->mutexs[0]);
	while (!is_time_to_die(bag))
	{
		;
	}
	pthread_mutex_unlock(&bag->config->mutexs[0]);
	pthread_exit(adress);
}
