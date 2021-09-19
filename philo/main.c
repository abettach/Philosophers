/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:30:33 by abettach          #+#    #+#             */
/*   Updated: 2021/09/15 17:52:00 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init2(t_args *args, int i)
{
	while (++i < args->philo_nb)
	{
		pthread_mutex_init(&args->fork[i], NULL);
		args->philo[i].args = args;
		args->philo[i].index = i;
		args->philo[i].right_fork = (i + 1) % args->philo_nb;
		args->philo[i].nbr_of_meal = 0;
		args->philo[i].already_eat = 0;
	}
}

void	ft_finish(t_philo *philo, int var)
{
	if (var == 1)
	{
		pthread_mutex_lock(&philo->args->print);
		printf("die %d\n", philo->index + 1);
		pthread_mutex_unlock(&philo->args->main);
	}
	if (var == 2)
	{
		pthread_mutex_lock(&philo->args->print);
		printf("simulation finished\n");
		pthread_mutex_unlock(&philo->args->main);
	}
}

void	*check_if_die(void *arg)
{
	t_philo	*philo;
	t_args	*args;

	philo = (t_philo *)arg;
	args = philo->args;
	philo->time_left_die = get_time() + args->time_to_die;
	while (1)
	{
		if (get_time() > philo->time_left_die
			&& philo->nbr_of_meal != args->nbr_must_eat)
			ft_finish(philo, 1);
		if (philo->nbr_of_meal == args->nbr_must_eat)
		{
			if (philo->already_eat == 0)
			{
				args->finished_eating++;
				philo->already_eat = 1;
			}
			if (args->finished_eating == args->philo_nb)
				ft_finish(philo, 2);
		}
		usleep(1000);
	}
}

void	*start_routine(void *arg)
{
	t_philo		*philo;
	t_args		*args;
	pthread_t	th;

	philo = (t_philo *)arg;
	args = philo->args;
	pthread_create(&th, NULL, &check_if_die, philo);
	pthread_detach(th);
	while (1)
	{
		pthread_mutex_lock(&args->fork[philo->index]);
		msg_print(philo, args, "🍴 take the left fork");
		pthread_mutex_lock(&args->fork[philo->right_fork]);
		msg_print(philo, args, "🍴 take the right fork");
		msg_print(philo, args, "🍔 is eating");
		philo->time_left_die = get_time() + args->time_to_die;
		usleep(args->time_to_eat * 1000);
		philo->nbr_of_meal++;
		ft_unlock_forks(args, philo);
		if (philo->nbr_of_meal == args->nbr_must_eat)
			pthread_mutex_lock(&args->stop);
		msg_print(philo, args, "💤 is sleeping");
		usleep(args->time_to_sleep * 1000);
		msg_print(philo, args, "🤔 is thinking");
	}
}

int	main(int ac, char **av)
{
	t_args		*args;
	pthread_t	th;
	int			i;

	if (ft_check(ac, av) == 0)
		printf("Error: Check your arguments\n");
	else
	{
		args = ft_init(ac, av, -1);
		i = -1;
		while (++i < args->philo_nb)
		{
			if (pthread_create(&th, NULL, &start_routine, &args->philo[i]))
				return (ft_free(args, "ERROR:create thread probleme\n"));
			pthread_detach(th);
			usleep(100);
		}
		pthread_mutex_lock(&args->main);
		pthread_mutex_unlock(&args->stop);
		return (ft_free(args, NULL));
	}
	return (ERROR);
}
