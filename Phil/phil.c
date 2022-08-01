/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tconwy <tconwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:32:26 by tconwy            #+#    #+#             */
/*   Updated: 2022/02/27 12:21:40 by tconwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

void	eat(int number, t_data *data)
{
	if (data->dead == false)
		lock_forks(number, data);
	if (data->dead == false)
		display_message(data, number, "is eating");
	data->phil[number].eat_count++;
	data->phil[number].time_last_eat = get_time(data);
	sleep2(data->time_to_eat);
	release_forks(number, data);
}

void	sleep_phil(t_data *data, int number)
{
	display_message(data, number, "is sleeping");
	sleep2(data->time_to_sleep);
}

void	*phil_life(void *phil1)
{
	t_phil	*phil;

	phil = (t_phil *)phil1;
	while (phil->data->dead == false)
	{
		if (phil->data->dead == false)
			eat(phil->index, phil->data);
		if (phil->data->count_eat != 0
			&& phil->eat_count == phil->data->count_eat)
			return (NULL);
		if (phil->data->dead == false)
			sleep_phil(phil->data, phil->index);
		if (phil->data->dead == false)
			display_message(phil->data, phil->index, "is thinking");
	}
	return (NULL);
}

bool	start_pr(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count_phil)
	{
		if (pthread_create(&data->phil[i].thread, NULL,
				&phil_life, &(data->phil[i])))
			return (1);
		i = i + 2;
	}
	sleep2(1);
	i = 1;
	while (i < data->count_phil)
	{
		if (pthread_create(&data->phil[i].thread, NULL,
				&phil_life, &(data->phil[i])))
			return (1);
		i = i + 2;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Error: arguments are entered incorrectly\n", 1);
		return (0);
	}
	if (check_arg(argc, argv) == 0)
	{
		ft_putstr_fd("Error: invalid value\n", 1);
		return (0);
	}
	if (data_init(&data, argc, argv) == 1)
		return (1);
	if (start_pr(&data) == 1)
		return (1);
	monitor(&data);
	sleep2(1);
	return (0);
}
