/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 06:17:49 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/22 22:31:27 by fgroo            ###   ########.fr       */
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
		return (exit(1), 1);
	calc_time(vars);
	print_args(vars, 'e', vars->philo_num);
	if (napping(vars->time_to_eat))
		return (exit(1), 1);
	sem_post(vars->forks);
	sem_post(vars->forks);
	sem_post(vars->butler);
	if (check_situation())
		return (exit(1), 1);
	++vars->eaten_count;
	if (check_situation())
		return (exit(1), 1);
	return (0);
}
