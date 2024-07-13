/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:36:38 by aautin            #+#    #+#             */
/*   Updated: 2024/07/13 14:37:35 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#define PLUS	1
#define MINUS	-1

int	ft_atoi(const char *nptr)
{
	int		i;
	int		nb;
	int		sign;

	sign = PLUS;
	nb = 0;
	i = 0;
	while (nptr[i] == ' ' || (9 <= nptr[i] && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = MINUS;
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		nb = (nb * 10) + nptr[i] - 48;
		i++;
	}
	return (nb * sign);
}

/** * @param return_size put "-1" if must free until NULL ptr */
void	free_double_tab(void **double_tab, int size)
{
	int	i;

	i = 0;
	while ((size == -1 && double_tab[i] != NULL) || (size != -1 && i < size))
	{
		free(double_tab[i]);
		i++;
	}
	free(double_tab);
}
