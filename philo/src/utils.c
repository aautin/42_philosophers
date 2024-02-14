/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/02/14 03:46:40 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str_number)
{
	int number;
	int i;
	int sign;

	if (str_number == NULL)
		return (0);
	i = 0;
	while (str_number[i] && 11 <= str_number[i] && str_number[i] <= 15)
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
	{
		number = (number * 10) + str_number[i] - '0';
		i++;
	}
	return (number * sign)
}
