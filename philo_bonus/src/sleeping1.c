/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 07:14:55 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/08 14:26:32 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stddef.h>
#include <unistd.h>

int	sleeping(t_vars *vars)
{
	if (vars->err)
		return (vars->finished_monitor = 1);
	print_args(vars, 's', vars->philo_num);
	usleep(vars->time_to_sleep * 1000);
	if (vars->err)
		return (vars->finished_monitor = 1);
	return (0);
}
