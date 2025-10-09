/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 06:17:49 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/08 14:28:26 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stddef.h>
#include <sys/time.h>
#include <unistd.h>

int	eating(t_vars *vars)
{
	if (vars->err)
		return (vars->finished_monitor = 1);
	print_args(vars, 'e', vars->philo_num);
	usleep(vars->time_to_eat * 1000);
	if (vars->err)
		vars->finished_monitor = 1;
	sem_post(vars->forks);
	sem_post(vars->forks);
	sem_post(vars->butler);
	if (vars->err)
		return (vars->finished_monitor = 1);
	calc_time(vars);
	++vars->eaten_count;
	if (vars->err)
		return (vars->finished_monitor = 1);
	return (0);
}
