/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 06:17:49 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/10 00:02:29 by fgroo            ###   ########.fr       */
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
	if (check_situation())
		return (1);
	print_args(vars, 'e', vars->philo_num);
	napping(vars->time_to_eat);
	calc_time(vars);
	sem_post(vars->forks);
	sem_post(vars->forks);
	sem_post(vars->butler);
	if (check_situation())
		return (1);
	++vars->eaten_count;
	if (check_situation())
		return (1);
	return (0);
}
