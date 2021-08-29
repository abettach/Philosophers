#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

t_vars       *ft_init(int ac, char **av, int  i)
{
    t_vars *vars;

    vars = (t_vars *)malloc(sizeof(t_vars));
    vars->philo_nb = ft_atoi(av[1]);
    vars->time_to_die = ft_atoi(av[2]);
    vars->time_to_eat = ft_atoi(av[3]);
    vars->time_to_sleep = ft_atoi(av[4]);
	vars->nbr_must_eat = (ac == 6) ? ft_atoi(av[5]) : -1;
	vars->philo_finished_eating = 0;
    vars->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * vars->philo_nb);
    vars->philo = (t_philo *)malloc(sizeof(t_philo) * vars->philo_nb);
    pthread_mutex_init(&vars->mutex_print, NULL);
    pthread_mutex_init(&vars->main_mutex,NULL);
    pthread_mutex_lock(&vars->main_mutex);
    vars->start_time = get_time();
    while (++i < vars->philo_nb)
	{
		pthread_mutex_init(&vars->fork[i], NULL);
	    vars->philo[i].vars = vars;
	    vars->philo[i].index = i;
	    vars->philo[i].right_fork = (i + 1) % vars->philo_nb;
	    vars->philo[i].meal_nbr = 0;
	    vars->philo[i].already_eat = 0;
	}
    return vars;
}

int     ft_check(int ac, char **av)
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

void	msg_print(t_philo *philo, t_vars *vars, char *msg)
{
	long	time;

	time = get_time() - vars->start_time;
	pthread_mutex_lock(&vars->mutex_print);
	printf("%ld\t%d\t%s\n", time, philo->index + 1, msg);
	pthread_mutex_unlock(&vars->mutex_print);
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