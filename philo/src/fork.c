/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 04:01:58 by aautin            #+#    #+#             */
/*   Updated: 2024/07/15 02:18:40 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"
#include "utils.h"
#include "philo.h"
#include "common.h"

void	lock_forks(t_sync_var *left, t_sync_var *right, int philo_index)
{
	if (philo_index % 2 == 1)
		pthread_mutex_lock(&left->mutex);
	pthread_mutex_lock(&right->mutex);
	if (philo_index % 2 == 0)
		pthread_mutex_lock(&left->mutex);
}

void	unlock_forks(t_sync_var *left, t_sync_var *right, int philo_index)
{
	if (philo_index % 2 == 1)
		pthread_mutex_unlock(&right->mutex);
	pthread_mutex_unlock(&left->mutex);
	if (philo_index % 2 == 0)
		pthread_mutex_unlock(&right->mutex);
}

void	free_forks(t_sync_var *left, t_sync_var *right, int philo_index)
{
	lock_forks(left, right, philo_index);
	left->var = FREE;
	right->var = FREE;
	unlock_forks(left, right, philo_index);	
}

int	take_forks(t_philo *philo)
{
	int	status;

	lock_forks(philo->left_fork, philo->right_fork, philo->index);
	if (philo->left_fork->var == FREE && philo->right_fork->var == FREE)
	{
		status = SUCCESS;
		philo->left_fork->var = TAKEN;
		philo->right_fork->var = TAKEN;
		print_state(philo->print, philo->timestamp, philo->index, FORK);
	}
	else
		status = FAILURE;
	unlock_forks(philo->left_fork, philo->right_fork, philo->index);
	return (status);
}
