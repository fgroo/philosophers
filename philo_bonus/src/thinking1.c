/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 06:34:46 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/08 14:26:21 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	thinking(t_vars *vars)
{
	if (vars->err)
		return (vars->finished_monitor = 1);
	print_args(vars, 't', vars->philo_num);
	return (0);
}
