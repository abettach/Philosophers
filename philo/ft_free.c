/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:06:43 by abettach          #+#    #+#             */
/*   Updated: 2021/09/15 16:36:04 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_unlock_forks(t_args *args, t_philo *philo)
{
	pthread_mutex_unlock(&args->fork[philo->index]);
	pthread_mutex_unlock(&args->fork[philo->right_fork]);
}

int	ft_free(t_args *args, char *msg)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&args->print);
	pthread_mutex_destroy(&args->main);
	while (++i < args->philo_nb)
		pthread_mutex_destroy(&args->fork[i]);
	if (args->fork)
		free(args->fork);
	if (args->philo)
	{
		free(args->philo);
		args->philo = NULL;
	}
	if (args)
	{
		free(args);
		args = NULL;
	}
	if (msg)
	{
		printf("%s", msg);
		return (ERROR);
	}
	return (0);
}
