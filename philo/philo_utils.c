/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:33:50 by abettach          #+#    #+#             */
/*   Updated: 2021/09/14 17:49:50 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

t_args	*ft_init(int ac, char **av, int i)
{
	t_args	*args;

	args = (t_args *)malloc(sizeof(t_args));
	args->philo_nb = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		args->nbr_must_eat = ft_atoi(av[5]);
	else
		args->nbr_must_eat = -1;
	args->philo_finished_eating = 0;
	args->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* args->philo_nb);
	args->philo = (t_philo *)malloc(sizeof(t_philo) * args->philo_nb);
	pthread_mutex_init(&args->print, NULL);
	pthread_mutex_init(&args->main, NULL);
	pthread_mutex_lock(&args->main);
	args->start_time = get_time();
	ft_init2(args, i);
	return (args);
}

int	ft_check(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 6 && ac != 5)
		return (0);
	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
	}
	return (1);
}

void	msg_print(t_philo *philo, t_args *args, char *msg)
{
	long	time;

	time = get_time() - args->start_time;
	pthread_mutex_lock(&args->print);
	printf("%ld\t%d\t%s\n", time, philo->index + 1, msg);
	pthread_mutex_unlock(&args->print);
}

int	ft_atoi(const char *str)
{
	int		s;
	long	r;

	s = 1;
	r = 0;
	while (*str == ' ' || *str == '\t' || *str == '\r'
		|| *str == '\n' || *str == '\v' || *str == '\f')
		str++;
	if (*str == '-')
		s = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		r = (r * 10) + (*str - '0');
		str++;
	}
	r = r * s;
	return (r);
}
