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
# include <pthread.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				index;
	struct s_vars	*vars;
	long			time_left_die;
	int				right_fork;
	int				meal_nbr;
	int				already_eat;
}	t_philo;

typedef struct s_vars
{
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				philo_nb;
	long			start_time;
	int				nbr_must_eat;
	int				philo_finished_eating;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	main_mutex;
	t_philo			*philo;
}	t_vars;

char	*ft_strdup(const char *s1);
int	     ft_atoi(const char *str);
t_vars   *ft_init(int ac, char **av, int i);
void     *ft_routine(void *arg);
long	  get_time(void);
void	  msg_print(t_philo *philo, t_vars *vars, char *msg);
int       ft_check(int ac, char **av);
#endif