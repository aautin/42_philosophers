/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:52:45 by aautin            #+#    #+#             */
/*   Updated: 2024/07/17 18:10:03 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_H
# define FORK_H

# include "monitor.h"

void	lock_forks(t_sync_var *left, t_sync_var *right, int philo_index);
void	unlock_forks(t_sync_var *left, t_sync_var *right, int philo_index);
int		take_forks(t_philo *philo);
void	free_forks(t_sync_var *left, t_sync_var *right, int philo_index);

#endif