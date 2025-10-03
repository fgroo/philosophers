/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dying1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:48:01 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/03 01:12:55 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	dying(t_vars *vars, size_t philo_num)
{
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;
	const size_t			left = philo_num - 1;
	const size_t			right = (philo_num % vars->philo_num);

	vars->err = 1;
	pthread_mutex_unlock(&vars->forks[left]);
	pthread_mutex_unlock(&vars->forks[right]);
	pthread_mutex_lock(&print_mutex);
	print_args(vars, 'd', philo_num);
	pthread_mutex_unlock(&print_mutex);
}
