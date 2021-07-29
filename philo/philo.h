/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 11:31:58 by abettach          #+#    #+#             */
/*   Updated: 2021/07/25 19:24:22 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
# include <sys/time.h>
typedef struct s_philo
{
    int num_philo;
    int time_eat;
    int time_die;
    int time_sleep;
    int num_time_eat;
}   t_philo;

char	*ft_strdup(const char *s1);
int	ft_atoi(const char *str);

#endif