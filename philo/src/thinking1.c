/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 06:34:46 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/03 02:25:01 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thinking(t_vars *vars, size_t philo_num)
{
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;

	if (vars->err)
		return (vars->err = 1);
	pthread_mutex_lock(&print_mutex);
	if (vars->err)
		return (pthread_mutex_unlock(&print_mutex), vars->err = 1);
	print_args(vars, 't', philo_num);
	pthread_mutex_unlock(&print_mutex);
	return (0);
}
