/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:43:50 by aautin            #+#    #+#             */
/*   Updated: 2024/02/28 17:56:04 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
