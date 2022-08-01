/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tconwy <tconwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:32:57 by tconwy            #+#    #+#             */
/*   Updated: 2022/02/25 14:36:18 by tconwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_data(t_data *data)
{
	free(data->pid1);
	if (data->phil)
		free(data->phil);
	sem_unlink("FORK");
	sem_unlink("DEAD");
	sem_unlink("WRITE");
	sem_unlink("EAT");
}

void	eat(int number, t_data *data)
{
	int	time_to_end_eating;

	lock_forks(number, data);
	sem_wait(data->write);
	display_message(data, number, "is eating");
	sem_post(data->write);
	data->phil->eat_count++;
	data->phil->time_last_eat = get_time(data);
	time_to_end_eating = data->phil->time_last_eat + data->time_to_eat;
	sleep2(data->time_to_eat);
	release_forks(data);
}

void	sleep_phil(t_data *data, int number)
{
	int	i;

	i = number;
	sem_wait(data->write);
	display_message(data, number, "is sleeping");
	sem_post(data->write);
	sleep2(data->time_to_sleep);
}

void	*phil_life(t_phil *phil)
{
	pthread_t	pth;

	pthread_create(&pth, NULL, &monitor, phil);
	while (1)
	{
		eat(phil->index, phil->data);
		sleep_phil(phil->data, phil->index);
		sem_wait(phil->data->write);
		display_message(phil->data, phil->index, "is thinking");
		sem_post(phil->data->write);
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	int			i;
	pthread_t	tid;

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
	if (data_create(&data, argc, argv) == 1)
		return (0);
	start_pr(&data);
	if (pthread_create(&tid, NULL, &monitor_eat_enough, &data) != 0)
		return (1);
	i = 0;
	sem_wait(data.dead1);
	while (i < data.count_phil)
		kill(data.phil[i++].pid, SIGTERM);
	free_data(&data);
	return (0);
}
