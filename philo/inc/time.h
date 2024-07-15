/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:52:45 by aautin            #+#    #+#             */
/*   Updated: 2024/07/15 00:23:34 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

# include <sys/time.h>
# include <unistd.h>

typedef struct timeval t_time;
typedef struct s_times {
	int	die;
	int	eat;
	int	sleep;
}	t_times;

#endif