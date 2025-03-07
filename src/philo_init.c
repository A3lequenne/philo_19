#include "philo.h"

int	init_philo(t_data *data)
{
	int	i;

	data->t_start = timestamp();
	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].n = i + 1;
		data->philo[i].last_eat = 0;
		data->philo[i].fork_r = NULL;
		data->philo[i].info = data;
		data->philo[i].m_count = 0;
		pthread_mutex_init(&(data->philo[i].fork_l), NULL);
		if (i == data->n_philo - 1)
			data->philo[i].fork_r = &data->philo[0].fork_l;
		else
			data->philo[i].fork_r = &data->philo[i + 1].fork_l;
		if (pthread_create(&data->philo[i].thread, NULL, \
				&philo_life, &(data->philo[i])) != 0)
			return (-1);
	}
	i = -1;
	while (++i < data->n_philo)
 		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (-1);
	return (0);
}

int	check_num(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **av)
{
    if (check_num(av))
    {
        printf("Invalid Arguments\n");
        return (1);
    }

    data->n_philo = ft_atoi(av[1]);
    if (data->n_philo <= 0)
    {
        printf("Invalid number of philosophers\n");
        return (1);
    }

    data->t_die = ft_atoi(av[2]);
    data->t_eat = ft_atoi(av[3]);
    data->t_sleep = ft_atoi(av[4]);
    if (av[5])
        data->n_eat = ft_atoi(av[5]);
    else
        data->n_eat = -1;

    pthread_mutex_init(&data->print, NULL);
    pthread_mutex_init(&data->m_stop, NULL);
    pthread_mutex_init(&data->m_eat, NULL);
    pthread_mutex_init(&data->dead, NULL);

    data->stop = 0;
    data->philo_eat = 0;

    data->philo = malloc(sizeof(t_global) * data->n_philo);
    if (data->philo == NULL)
    {
        printf("Malloc Error\n");
        return (1);
    }

    return (0);
}