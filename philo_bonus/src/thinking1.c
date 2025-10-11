/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 06:34:46 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/11 13:34:40 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	thinking(t_vars *vars)
{
	if (check_situation())
		return (exit(1), 1);
	print_args(vars, 't', vars->philo_num);
	if (check_situation())
		return (exit(1), 1);
	return (0);
}
