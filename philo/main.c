#include "philo.h"

int    ft_get_args(t_philo *p, char **av)
{
    p->num_philo = ft_atoi(av[1]);
    p->time_die = ft_atoi(av[2]);
    p->time_eat = ft_atoi(av[3]);
    p->time_sleep = ft_atoi(av[4]);
    if (av[5])
    {
        p->num_time_eat = ft_atoi(av[5]);
        if (p->num_time_eat < 0)
            return 0;
    }
    else
        p->num_time_eat = -1;
    if (p->num_philo <= 0 || p->time_die < 0 || p->time_eat < 0 || p->time_sleep < 0)
        return 0;
    return 1;
}
uint64_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int     main(int ac, char **av)
{
    t_philo p;
    int i = 0;
    uint64_t time = 0;
    uint64_t time2 = 0;
    uint64_t start = 0;
    if (ft_get_args(&p, av) == 0)
        return 0;
    start = get_time();
    while (i < p.num_philo)
    {
        time2 = time - start;
        printf("time = %llu\n",time2);
        i++;
    }
    
    return 0;
}