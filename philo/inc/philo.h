/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:47:36 by fgroo             #+#    #+#             */
/*   Updated: 2025/09/01 21:49:58 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <pthread.h>
# include <time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_vars
{
    int				err;
    size_t			philo_num;
    size_t			time_to_die;
    size_t			time_to_eat;
    size_t			time_to_sleep;
    pthread_t       *philos;
    pthread_mutex_t *forks;
    size_t			turns;
}	t_vars;

void    print_args(size_t time, char type, size_t philo_num);

#endif
