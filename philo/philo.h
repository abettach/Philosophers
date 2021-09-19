/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 11:31:58 by abettach          #+#    #+#             */
/*   Updated: 2021/09/19 17:35:47 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# define ERROR 1

typedef struct s_philo
{
	int				index;
	struct s_args	*args;
	long			time_left_die;
	int				right_fork;
	int				left_fork;
	int				nbr_of_meal;
	int				already_eat;
}	t_philo;

typedef struct s_args
{
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				philo_nb;
	long			start_time;
	int				nbr_must_eat;
	int				finished_eating;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	main;
	pthread_mutex_t	stop;
	t_philo			*philo;
}	t_args;

char		*ft_strdup(const char *s1);
int			ft_atoi(const char *str);
t_args		*ft_init(int ac, char **av, int i);
void		*start_routine(void *arg);
long		get_time(void);
void		msg_print(t_philo *philo, t_args *args, char *msg);
int			ft_check(int ac, char **av);
void		ft_init2(t_args *args, int i);
int			ft_free(t_args *args, char *msg, int i);
void		ft_unlock_forks(t_args *args, t_philo *philo);

#endif