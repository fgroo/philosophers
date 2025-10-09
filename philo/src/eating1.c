/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 06:17:49 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/09 22:10:45 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stddef.h>
#include <sys/time.h>
#include <unistd.h>

int	eating(t_vars *vars, size_t philo_num)
{
	const size_t			left = philo_num - 1;
	const size_t			right = (philo_num % vars->philo_num);

	if (vars->err)
		return (pthread_mutex_unlock(&vars->forks[left]),
			pthread_mutex_unlock(&vars->forks[right]), 1);
	print_args(vars, 'e', philo_num);
	if (napping(vars, vars->time_to_eat))
		return (pthread_mutex_unlock(&vars->forks[left]),
			pthread_mutex_unlock(&vars->forks[right]), 1);
	calc_time(vars, philo_num);
	pthread_mutex_unlock(&vars->forks[left]);
	pthread_mutex_unlock(&vars->forks[right]);
	++vars->eaten_count[philo_num];
	if (vars->err)
		return (1);
	return (0);
}
