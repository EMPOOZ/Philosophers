/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tconwy <tconwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:32:36 by tconwy            #+#    #+#             */
/*   Updated: 2022/02/25 14:32:37 by tconwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long long	get_total_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((long)tv.tv_sec * 1000) + ((long)tv.tv_usec / 1000));
}

unsigned long long	get_time(t_data *data)
{
	return ((get_total_time() - data->time_to_start));
}

void	create_phil(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count_phil)
	{
		data->phil[i].index = i;
		data->phil[i].eat_count = 0;
		data->phil[i].data = data;
		data->phil[i].time_last_eat = 0;
		i++;
	}
}

void	sem_create1(t_data *data)
{
	sem_unlink("FORK");
	data->sem = sem_open("FORK", O_CREAT, 0644, data->count_phil);
	sem_unlink("DEAD");
	data->dead1 = sem_open("DEAD", O_CREAT, 0644, 0);
	sem_unlink("WRITE");
	data->write = sem_open("WRITE", O_CREAT, 0644, 1);
	sem_unlink("EAT");
	data->eat = sem_open("EAT", O_CREAT, 0644, 0);
}

int	data_create(t_data *data, int argc, char **argv)
{
	data->count_phil = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->count_eat = ft_atoi(argv[5]);
		if (data->count_eat == 0)
			exit (1);
	}
	else
		data->count_eat = 0;
	data->phil = NULL;
	data->pid1 = malloc(sizeof(int) * data->count_phil);
	if (!data->pid1)
		return (1);
	sem_create1(data);
	data->time_to_start = get_time(data);
	data->phil = (t_phil *)malloc(sizeof(t_phil) * data->count_phil);
	if (!data->phil)
		return (1);
	create_phil(data);
	return (0);
}
