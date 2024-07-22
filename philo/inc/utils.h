/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:37:43 by aautin            #+#    #+#             */
/*   Updated: 2024/07/22 17:30:53 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "thread.h"
# include "philo.h"
# include "time.h"

# define FRAGMENT_SIZE	500

void	free_double_tab(void **double_tab, int size);
int		get_time_spend(t_time start_times);
int		print_state(t_philo *philo, int action);
int		time_left_until_die(int time_to_die, t_time lastmeal);
int		fragmented_usleep(int time, int activity_time, t_philo *philo);

#endif