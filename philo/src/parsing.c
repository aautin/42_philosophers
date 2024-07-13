/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/07/13 14:38:49 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "config.h"
#include "philo.h"
#include "utils.h"

static int	is_argc_correct(int argc)
{
	if (argc == 4 || argc == 5)
		return (TRUE);
	printf("Error\nThe args must be: ");
	printf("philos_nb time_to_die time_to_eat time_to_sleep [meals_to_eat]\n");
	return (FALSE);
}

static int	are_argv_correct(t_config *config)
{
	if (config->philos_nb > 0 && config->time_to_die > 0
		&& config->time_to_eat > 0 && config->time_to_sleep > 0
		&& (config->meals_to_eat == NO_MEALS_LIMIT || config->meals_to_eat > 0))
		return (TRUE);
	printf("Error\nEach argument must be strictely positive nbr\n");
	return (FALSE);
}

static void	init_config(t_config *config, int argc, char *argv[])
{
	config->philos_nb = ft_atoi(argv[0]);
	config->time_to_die = ft_atoi(argv[1]);
	config->time_to_eat = ft_atoi(argv[2]);
	config->time_to_sleep = ft_atoi(argv[3]);

	if (argc == 5)
	{
		config->meals_to_eat = ft_atoi(argv[4]);
		if (config->meals_to_eat == NO_MEALS_LIMIT)
			config->meals_to_eat--;
	}
	else
		config->meals_to_eat = NO_MEALS_LIMIT;	
}

t_config	*get_config(int argc, char *argv[])
{
	t_config	*config;

	if (!is_argc_correct(argc))
		return (NULL);

	config = malloc(sizeof(*config));
	if (config == NULL)
	{
		perror("get_config():malloc()");
		return (NULL);
	}
	init_config(config, argc, argv);

	if (are_argv_correct(config))
		return (config);
	free(config);
	return (NULL);
}
