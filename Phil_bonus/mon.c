/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mon.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tconwy <tconwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:32:52 by tconwy            #+#    #+#             */
/*   Updated: 2022/02/25 14:36:21 by tconwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_message(t_data *data, int number, char *str_err)
{
	printf("%llu	%d number %s\n", get_time(data), number, str_err);
}

bool	check_philo(t_phil *phil)
{
	if (phil->data->time_to_die < get_time(phil->data) - phil->time_last_eat)
	{
		display_message(phil->data, phil->index, "died");
		sem_post(phil->data->dead1);
		return (false);
	}
	if (phil->data->count_eat != 0 && phil->eat_count == phil->data->count_eat)
	{
		sem_post(phil->data->eat);
		return (false);
	}
	return (true);
}

void	*monitor(void *phil1)
{
	t_phil		*phil;

	phil = (t_phil *)phil1;
	while (1)
	{
		if (!check_philo(phil))
			break ;
		sleep2(10);
	}
	return (0);
}
