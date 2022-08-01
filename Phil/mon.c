/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mon.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tconwy <tconwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:32:20 by tconwy            #+#    #+#             */
/*   Updated: 2022/02/27 12:12:56 by tconwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

void	display_message(t_data *data, int number, char *str_err)
{
	printf("%llu	%d number %s\n", get_time(data), number + 1, str_err);
}

int	check_philo(t_phil *philo)
{
	if (philo->data->time_to_die
		< get_time(philo->data) - philo->time_last_eat)
	{
		philo->data->dead = true;
		display_message(philo->data, philo->index, "died");
		pthread_mutex_unlock(&philo->mutex);
		return (1);
	}
	return (0);
}

void	monitor(t_data *data)
{
	int	i;

	while (1)
	{
		sleep2(9);
		i = 0;
		while (data->count_eat != 0 && i < data->count_phil)
		{
			if (data->phil[i].eat_count != data->count_eat)
				break ;
			i++;
		}
		if (i == data->count_phil)
			return ;
		i = 0;
		while (i < data->count_phil)
		{
			if (data->count_eat == 0
				|| data->phil[i].eat_count != data->count_eat)
				if (check_philo(&data->phil[i]) == 1)
					return ;
			i++;
		}
	}
}
