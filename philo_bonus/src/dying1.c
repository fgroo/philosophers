/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dying1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:48:01 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/06 16:10:35 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	dying(t_vars *vars, size_t philo_num)
{
	vars->err = 1;
	print_args(vars, 'd', philo_num);
	kill(vars->philos[philo_num], 1);
}
