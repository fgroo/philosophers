/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 06:34:46 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/23 11:52:02 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h>

int	thinking(t_vars *vars)
{
	if (check_situation())
		return (exit(1), 1);
	print_args(vars, 't', vars->philo_num);
	if (check_situation())
		return (exit(1), 1);
	usleep(1042);
	return (0);
}
