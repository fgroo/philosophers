/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 06:17:49 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/01 23:03:40 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stddef.h>
#include <sys/time.h>
#include <unistd.h>

void	eating(t_vars *vars, size_t philo_num)
{
	struct timeval			tv;
	const size_t			cur_time = (gettimeofday(&tv, NULL) * 0)
		+ conv_time(tv.tv_sec, tv.tv_usec, vars->start_sec, vars->start_usec);
	const size_t			left = philo_num - 1;
	const size_t			right = (philo_num % vars->philo_num);

	if (cur_time - vars->timestamp[philo_num] > vars->time_to_die * 1000)
	{
		dying(vars, philo_num);
		return ;
	}
	print_args(vars, 'e', philo_num);
	usleep(vars->time_to_eat * 1000);
	calc_time(vars, philo_num);
	pthread_mutex_lock(&vars->eaten_mutex[philo_num]);
	++vars->eaten_count[philo_num];
	pthread_mutex_unlock(&vars->eaten_mutex[philo_num]);
	pthread_mutex_unlock(&vars->forks[left]);
	pthread_mutex_unlock(&vars->forks[right]);
}
