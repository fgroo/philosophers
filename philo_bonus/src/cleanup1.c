/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:45:55 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/06 23:13:35 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>
#include <stddef.h>


void	cleanup(t_vars *vars)
{
	if (vars->philos)
		free(vars->philos);
	if (!vars->forks_init)
		sem_destroy(&vars->forks);
	if (!vars->butler_init)
		sem_destroy(&vars->butler);
	if (!vars->print_init)
		sem_destroy(&vars->print);
}
