/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/02/20 16:03:37 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	are_argvs_correct(int argc, char *argv[])
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

static void	launch_simulation(t_table *table, char *argv[], unsigned short nb)
{
	int			i;
	t_bag		*bag;
	t_bag		*adress;

	i = 0;
	while (i < nb)
	{
		bag = (t_bag *)malloc(sizeof(t_bag));
		bag->time = (t_timers *)malloc(sizeof(t_timers));
		bag->i = (unsigned short *)malloc(sizeof(unsigned short));
		bag->philos_nb = (unsigned short *)malloc(sizeof(unsigned short));
		bag->meals_left = (int *)malloc(sizeof(int));
		bag->table = table;
		*bag->i = i;
		*bag->philos_nb = nb;
		if (argv[5] == NULL)
			*bag->meals_left = -1;
		else
			*bag->meals_left = ft_atou(argv[5]);
		set_timers(bag->time, argv);
		pthread_create(&table->philos[i++], NULL, &simulation, bag);
	}
	i = 0;
	while (i < nb)
	{
		pthread_join(table->philos[i++], (void **) &adress);
		free_bag(adress);
	}
}

int	main(int argc, char *argv[])
{
	t_table			table;
	unsigned short	philos_nb;

	if (argc == 5 || argc == 6)
	{
		if (are_argvs_correct(argc, argv) == 0)
			return (1);
		philos_nb = (unsigned short) ft_atou(argv[1]);
		if (set_table(&table, philos_nb) == 1)
			return (1);
		launch_simulation(&table, argv, philos_nb);
		free_table(&table, philos_nb);
		return (0);
	}
	else
	{
		printf("Wrong arguments\nMust be: ");
		printf("nb_of_philos time_to_die _eat _sleep [meals_philos_must_eat]\n");
		return (1);
	}
}
