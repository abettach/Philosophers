/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:06:43 by abettach          #+#    #+#             */
/*   Updated: 2021/09/14 17:32:43 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
