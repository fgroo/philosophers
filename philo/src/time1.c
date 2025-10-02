/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:26:01 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/02 23:37:34 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stddef.h>
#include <sys/time.h>

int	calc_time(t_vars *vars, size_t philo_num)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	static int				firstrun = 0;

	pthread_mutex_lock(&mutex);
	if (gettimeofday(&vars->tv, NULL))
		cleanup(vars, 0);
	if (!firstrun)
	{
		vars->start_sec = (size_t)vars->tv.tv_sec;
		vars->start_usec = (size_t)vars->tv.tv_usec;
		++firstrun;
	}
	vars->cur_sec[philo_num] = vars->tv.tv_sec - vars->start_sec;
	vars->cur_usec[philo_num] = vars->tv.tv_usec - vars->start_usec;
	if ((size_t)vars->tv.tv_usec < vars->start_usec)
	{
		vars->cur_sec[philo_num]--;
		vars->cur_usec[philo_num] = vars->cur_usec[philo_num] + 1000000L;
	}
	vars->timestamp[philo_num] = vars->cur_sec[philo_num]
		* 1000000L + vars->cur_usec[philo_num];
	pthread_mutex_unlock(&mutex);
	return (0);
}

size_t	conv_time(long sec, long usec, size_t s_sec, size_t s_usec)
{
	size_t	new;

	sec = sec - s_sec;
	usec = usec - s_usec;
	if (usec < 0 && sec--)
		usec += 1000000L;
	new = (size_t)sec * 1000000L + usec;
	return (new);
}

