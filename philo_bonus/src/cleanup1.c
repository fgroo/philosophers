/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:45:55 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/11 21:12:19 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	cleanup(t_vars *vars)
{
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
	sem_close(vars.stop);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_butler");
	sem_unlink("/philo_print");
	sem_unlink("/philo_stop");
}

int	check_situation(void)
{
	sem_t	*temp_stop;

	temp_stop = sem_open("/philo_stop", 0);
	if (temp_stop == SEM_FAILED)
		return (1);
	sem_close(temp_stop);
	return (0);
}
