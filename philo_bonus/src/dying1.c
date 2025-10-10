/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dying1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:48:01 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/10 10:09:02 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

void	dying(t_vars *vars, size_t philo_num)
{
	if (vars->err || check_situation())
		return ;
	vars->err = 1;
	sem_unlink("/philo_stop");
	print_args(vars, 'd', philo_num);
}
