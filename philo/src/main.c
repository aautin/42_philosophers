/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/03/03 13:52:18 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "config.h"

int	main(int argc, char *argv[])
{
	t_preconfig	*preconfig;

	preconfig = get_preconfig(argc - 1, argv + 1);
	if (preconfig == NULL)
		return (EXIT_FAILURE);

	// here start the execution ...

	free(preconfig);
	return (EXIT_SUCCESS);
}
