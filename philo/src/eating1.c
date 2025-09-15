/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 06:17:49 by fgroo             #+#    #+#             */
/*   Updated: 2025/09/15 16:49:53 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stddef.h>
#include <sys/time.h>
#include <unistd.h>

void	eating(t_vars *vars, size_t philo_num)
{
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;
	const size_t			left = philo_num - 1;
	const size_t			right = (philo_num % vars->philo_num);

	pthread_mutex_lock(&print_mutex);
	print_args(vars, 'e', philo_num);
	usleep(vars->time_to_eat * 1000);
	if (gettimeofday(&vars->start_time[philo_num], NULL) && vars->start_time[philo_num].tv_usec - (long)vars->elapsed_time > (long)vars->time_to_eat)
		return ;
	pthread_mutex_unlock(&print_mutex);
	pthread_mutex_lock(&vars->eaten_mutex[philo_num]);
	++vars->eaten_count;
	pthread_mutex_unlock(&vars->eaten_mutex[philo_num]);
	pthread_mutex_unlock(&vars->forks[left]);
	pthread_mutex_unlock(&vars->forks[right]);
}
