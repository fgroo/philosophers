/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:59:52 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/09 23:12:17 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <bits/pthreadtypes.h>
#include <sched.h>
#include <stddef.h>
#include <semaphore.h>

static int	create_forks_butler_print(t_vars *vars)
{
	vars->forks = sem_open("/philo_forks", O_CREAT | O_EXCL, 0644,
			vars->philo_num);
	if (vars->forks == SEM_FAILED)
		return (1);
	else
		vars->forks_init = 1;
	vars->butler = sem_open("/philo_butler", O_CREAT | O_EXCL, 0644,
			vars->philo_num - 1);
	if (vars->butler == SEM_FAILED)
		return (1);
	else
		vars->butler_init = 1;
	vars->print = sem_open("/philo_print", O_CREAT | O_EXCL, 0644, 1);
	if (vars->print == SEM_FAILED)
		return (1);
	else
		vars->print_init = 1;
	vars->stop = sem_open("/philo_stop", O_CREAT | O_EXCL, 0644, 0);
	if (vars->stop == SEM_FAILED)
		return (1);
	else
		vars->stop_init = 1;
	return (0);
}

int	creating(t_vars *vars)
{
	int	err_flag;

	vars->philos = malloc(sizeof(pid_t) * (vars->philo_num + 2));
	if (!vars->philos)
		return (err_flag = 1);
	vars->philos[0] = 0;
	vars->philos[vars->philo_num + 1] = 0;
	err_flag = 0;
	if (create_forks_butler_print(vars))
		err_flag = 1;
	return (err_flag);
}
