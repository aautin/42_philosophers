/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:52:45 by aautin            #+#    #+#             */
/*   Updated: 2024/03/03 15:02:35 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

typedef struct s_preconfig {
	int	philos_nb;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals_to_eat;
}	t_preconfig;

t_preconfig	*get_preconfig(int argc, char *argv[]);

#endif