/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 07:14:55 by fgroo             #+#    #+#             */
/*   Updated: 2025/09/02 10:38:05 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stddef.h>

void	sleeping(t_vars *vars, size_t philo_num)
{
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&print_mutex);
	print_args(vars, 's', philo_num);
	usleep(vars->time_to_sleep * 1000);
	pthread_mutex_unlock(&print_mutex);
}
