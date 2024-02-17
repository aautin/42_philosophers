/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/02/17 21:28:47 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	launch_simulation(t_table *table, char *argv[], unsigned short nb)
{
	int				i;
	t_bag		*bag;
	t_bag		*adress;

	i = 0;
	while (i < nb)
	{
		bag = (t_bag *)malloc(sizeof(t_bag));
		bag->time = (t_timers *)malloc(sizeof(t_timers));
		bag->i = (unsigned short *)malloc(sizeof(unsigned short));
		bag->philos_nb = (unsigned short *)malloc(sizeof(unsigned short));
		bag->table = table;
		*bag->i = i;
		*bag->philos_nb = nb;
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

	if (argc == 5)
	{
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
		printf("nb_of_philosophers time_to_die time_to_eat time_to_sleep\n");
		return (1);
	}
}
