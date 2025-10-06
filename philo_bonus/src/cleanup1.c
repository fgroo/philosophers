/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:45:55 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/06 16:04:40 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>
#include <stddef.h>


void	cleanup(t_vars *vars)
{
	if (!vars->forks_init)
		sem_destroy(&vars->forks);
	if (!vars->butler_init)
		sem_destroy(&vars->butler);
	if (vars->philos)
	{
		free(vars->philos);
		vars->philos = NULL;
	}
}
