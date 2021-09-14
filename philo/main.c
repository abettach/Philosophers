#include "philo.h"

int	ft_free(t_vars *vars, char *msg)
{
	int i;

	i = -1;
	if (vars)
	{
		pthread_mutex_destroy(&vars->mutex_print);
		pthread_mutex_destroy(&vars->main_mutex);
		while (++i < vars->philo_nb)
			pthread_mutex_destroy(&vars->fork[i]);
		free(vars);
		vars = NULL;
	}
	if (vars && vars->fork)
		free(vars->fork);
	if (vars && vars->philo)
	{
		free(vars->philo);
		vars->philo = NULL;
	}
	if (msg)
	{
		printf("%s", msg);
		return (ERROR);
	}
	return (0);
}

void    *check_if_die(void *arg)
{
	t_philo	*philo;
	t_vars	*vars;

	philo = (t_philo *)arg;
	vars = philo->vars;
	philo->time_left_die = get_time() + vars->time_to_die;
    while (1)
	{
		if (get_time() > philo->time_left_die)
		{
			pthread_mutex_lock(&philo->vars->mutex_print);
			printf("die %d\n", philo->index + 1);
			pthread_mutex_unlock(&philo->vars->main_mutex);
		}
        if (philo->meal_nbr == vars->nbr_must_eat)
		{
	        pthread_mutex_lock(&philo->vars->mutex_print);
	        printf("simulation finished: philo %d\n", philo->index + 1);
	        pthread_mutex_unlock(&philo->vars->main_mutex);
        }
		usleep(1000);
	}
}

void    *start_routine(void *arg)
{
    t_philo *philo;
    t_vars *vars;
    pthread_t th;

    philo = (t_philo *)arg;
    vars = philo->vars;
    pthread_create(&th, NULL, &check_if_die, philo);
    pthread_detach(th);
    while (1)
    {
        pthread_mutex_lock(&vars->fork[philo->index]);
	    msg_print(philo, vars, "🍴 take a fork");
	    pthread_mutex_lock(&vars->fork[philo->right_fork]);
	    msg_print(philo, vars, "🍴 take a the right fork");
        msg_print(philo, vars, "🍔 is eating");
	    philo->time_left_die = get_time() + vars->time_to_die;
	    usleep(vars->time_to_eat * 1000);
	    philo->meal_nbr++;
	    pthread_mutex_unlock(&vars->fork[philo->index]);
	    pthread_mutex_unlock(&vars->fork[philo->right_fork]);
	    msg_print(philo, vars, "💤 is sleeping");
	    usleep(vars->time_to_sleep * 1000);
	    msg_print(philo, vars, "🤔 is thinking");
    }
}

int     main(int ac, char **av)
{
    t_vars *vars;
    pthread_t th;
    int i;

    if (ft_check(ac, av) == 0)
		printf("Error: Check your arguments\n");
    else
    {
        vars = ft_init(ac, av, -1);
        i = -1;
        while (++i < vars->philo_nb)
        {
            if (pthread_create(&th, NULL, &start_routine, &vars->philo[i]))
				return (ft_free(vars, "ERROR:create thread probleme\n"));
            pthread_detach(th);
            usleep(100);
        }
        pthread_mutex_lock(&vars->main_mutex);
    	return (ft_free(vars, NULL));
    }
	return (ERROR);
}