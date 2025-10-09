/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:45:55 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/09 14:14:26 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>
#include <stddef.h>

void	cleanup(t_vars *vars)
{
	if (vars->forks_init && vars->print != SEM_FAILED)
		sem_close(vars->forks);
	if (vars->butler_init && vars->print != SEM_FAILED)
		sem_close(vars->butler);
	if (vars->print_init && vars->print != SEM_FAILED)
		sem_close(vars->print);
	if (vars->philos)
		(free(vars->philos), vars->philos = NULL);
}

void	killer(t_vars *vars)
{
	size_t	i;

	i = 1;
	vars->err = 1;
	while (vars->philos[i])
		kill(vars->philos[i++], SIGTERM);
}

void	sem_closing(t_vars vars)
{
	sem_close(vars.forks);
	sem_close(vars.butler);
	sem_close(vars.print);
}
