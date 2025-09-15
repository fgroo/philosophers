/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dying1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:48:01 by fgroo             #+#    #+#             */
/*   Updated: 2025/09/15 16:48:14 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	dying(t_vars *vars, size_t philo_num)
{
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&print_mutex);
	print_args(vars, 'c', philo_num);
	cleanup(vars, 0);
	pthread_mutex_unlock(&print_mutex);
}
