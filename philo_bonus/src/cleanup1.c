/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:45:55 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/07 18:05:51 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>
#include <stddef.h>


void	cleanup(t_vars *vars)
{
	if (vars->forks_init || vars->forks != SEM_FAILED)
		sem_unlink("/philo_forks"), sem_close(vars->forks);
	if (vars->butler_init || vars->butler != SEM_FAILED)
		sem_unlink("/philo_butler"), sem_close(vars->butler);
	if (vars->print_init || vars->print != SEM_FAILED)
		sem_unlink("/philo_print"), sem_close(vars->print);
	if (vars->philos)
		free(vars->philos);
	// if (!vars->forks_init)
	// 	sem_destroy(&vars->forks);
	// if (!vars->butler_init)
	// 	sem_destroy(&vars->butler);
	// if (!vars->print_init)
	// 	sem_destroy(&vars->print);

}
