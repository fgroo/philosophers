/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 07:14:55 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/22 22:30:51 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stddef.h>
#include <unistd.h>

int	sleeping(t_vars *vars)
{
	if (check_situation())
		return (exit(1), 1);
	print_args(vars, 's', vars->philo_num);
	if (check_situation())
		return (exit(1), 1);
	if (napping(vars->time_to_sleep))
		return (exit(1), 1);
	return (0);
}
