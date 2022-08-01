/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tconwy <tconwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:51:14 by tconwy            #+#    #+#             */
/*   Updated: 2022/02/27 12:11:22 by tconwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

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

void	init_phil(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count_phil)
	{
		data->phil[i].index = i;
		data->phil[i].eat_count = 0;
		data->phil[i].data = data;
		data->phil[i].time_last_eat = 0;
		pthread_mutex_init(&data->phil[i].mutex, NULL);
		i++;
	}
}

int	data_init(t_data *data, int argc, char **argv)
{
	data->count_phil = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->count_eat = ft_atoi(argv[5]);
		if (data->count_eat == 0)
			return (1);
	}
	else
		data->count_eat = 0;
	data->phil = NULL;
	data->dead = false;
	data->time_to_start = get_time(data);
	data->phil = (t_phil *)malloc(sizeof(t_phil) * data->count_phil);
	if (!data->phil)
		return (1);
	init_phil(data);
	return (0);
}
