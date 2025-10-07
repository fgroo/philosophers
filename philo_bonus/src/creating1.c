/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:59:52 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/07 18:10:59 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <bits/pthreadtypes.h>
#include <sched.h>
#include <stddef.h>
#include <semaphore.h>

static int	create_forks_butler_print(t_vars *vars)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_butler");
	sem_unlink("/philo_print");
	// vars->forks = malloc(sizeof(sem_t));
	// vars->butler = malloc(sizeof(sem_t));
	// vars->print = malloc(sizeof(sem_t));
	// if (!vars->forks || !vars->butler || !vars->print)
	// 	return (1);
	vars->forks = sem_open("/philo_forks", O_CREAT | O_EXCL, 0644, vars->philo_num);
	if (vars->forks == SEM_FAILED)
		return (1);
	else
		vars->forks_init = 1;
	vars->butler = sem_open("/philo_butler", O_CREAT | O_EXCL, 0644, vars->philo_num - 1);
	if (vars->butler == SEM_FAILED)
		return (1);
	else
		vars->butler_init = 1;
	vars->print = sem_open("/philo_print", O_CREAT | O_EXCL, 0644, 1);
	if (vars->print == SEM_FAILED)
		return (1);
	else
		vars->print_init = 1;

	return (0);
}

int	creating(t_vars *vars)
{
	int	err_flag;
	
	vars->philos = malloc(sizeof(pid_t) * (vars->philo_num + 1));
	if (!vars->philos)
		return (err_flag = 1);
	err_flag = 0;
	if (create_forks_butler_print(vars))
		err_flag = 1;
	return (err_flag);
}
