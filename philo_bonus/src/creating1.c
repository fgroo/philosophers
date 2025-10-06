/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:59:52 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/06 16:05:38 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <bits/pthreadtypes.h>
#include <sched.h>
#include <stddef.h>
#include <semaphore.h>

static int	create_forks_and_butler(t_vars *vars)
{
	int		err;

	err = sem_init(&vars->forks, PTHREAD_PROCESS_SHARED, vars->philo_num);
	if (err != 0)
		return (sem_destroy(&vars->forks), 1);
	else
	 	vars->forks_init = 1;
	err = sem_init(&vars->butler, PTHREAD_PROCESS_SHARED, vars->philo_num - 1);
	if (err != 0)
		return (sem_destroy(&vars->forks), 1);
	else
	 	vars->butler_init = 1;
	return (0);
}

int	creating(t_vars *vars)
{
	int	err_flag;
	
	vars->philos = malloc(sizeof(pid_t) * vars->philo_num);
	if (vars->philos)
		return (err_flag = 1);
	err_flag = 0;
	if (create_forks_and_butler(vars))
		err_flag = 1;
	return (err_flag);
}
