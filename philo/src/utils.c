/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/02/15 16:35:19 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str_number)
{
	int	number;
	int	i;
	int	sign;

	if (str_number == NULL)
		return (0);
	i = 0;
	while ((9 <= str_number[i] && str_number[i] <= 13) || str_number[i] == ' ')
		i++;
	sign = 1;
	if (str_number[i] == '-' || str_number[i] == '+')
	{
		if (str_number[i] == '-')
			sign = -1;
		i++;
	}
	while (str_number[i] == '0')
		i++;
	number = 0;
	while ('0' <= str_number[i] && str_number[i] <= '9')
		number = (number * 10) + str_number[i++] - '0';
	return (number * sign);
}

t_time	get_current_time(t_config *config)
{
	t_time	current_local;
	t_time	current_global;

	gettimeofday(&current_global, NULL);
	current_local.tv_sec = current_global.tv_sec - config->start.tv_sec;
	current_local.tv_usec = current_global.tv_usec - config->start.tv_usec;
	return (current_local);
}
