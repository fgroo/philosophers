/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:26:01 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/11 21:03:39 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	calc_time(t_vars *vars)
{
	static int				firstrun = 0;

	if (gettimeofday(&vars->tv, NULL))
		cleanup(vars);
	if (!firstrun)
	{
		vars->start_sec = (size_t)vars->tv.tv_sec;
		vars->start_usec = (size_t)vars->tv.tv_usec;
		++firstrun;
	}
	vars->cur_sec = vars->tv.tv_sec - vars->start_sec;
	vars->cur_usec = vars->tv.tv_usec - vars->start_usec;
	if ((size_t)vars->tv.tv_usec < vars->start_usec)
	{
		vars->cur_sec--;
		vars->cur_usec = vars->cur_usec + 1000000L;
	}
	vars->timestamp = vars->cur_sec
		* 1000000L + vars->cur_usec;
	return (0);
}

size_t	conv_time(long sec, long usec, size_t s_sec, size_t s_usec)
{
	size_t	new;
	long	sec_diff;
	long	usec_diff;

	sec_diff = sec - (long)s_sec;
	usec_diff = usec - (long)s_usec;
	if (usec_diff < 0)
	{
		--sec_diff;
		usec_diff += 1000000L;
	}
	if (sec_diff < 0)
		return (0);
	new = (size_t)sec_diff * 1000000L + usec_diff;
	return (new);
}
