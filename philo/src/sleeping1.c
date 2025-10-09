/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 07:14:55 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/09 22:10:36 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stddef.h>
#include <unistd.h>

int	sleeping(t_vars *vars, size_t philo_num)
{
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&print_mutex);
	if (vars->err)
		return (pthread_mutex_unlock(&print_mutex), vars->err = 1);
	print_args(vars, 's', philo_num);
	pthread_mutex_unlock(&print_mutex);
	if (napping(vars, vars->time_to_sleep))
		return (pthread_mutex_unlock(&print_mutex), vars->err = 1);
	if (vars->err)
		return (vars->err = 1);
	return (0);
}
