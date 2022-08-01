/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tconwy <tconwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:32:42 by tconwy            #+#    #+#             */
/*   Updated: 2022/02/25 14:32:43 by tconwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_arg(int argc, char **argv)
{
	int	i;
	int	i1;
	int	y;

	y = 0;
	i1 = 0;
	i = 1;
	if (argc == 2)
		i = 0;
	while (argv[i])
	{
		y = 0;
		i1 = 0;
		while (argv[i][i1])
		{
			if (argv[i][i1] < '0' || argv[i][i1] > '9')
				return (0);
			i1++;
		}
		i++;
	}
	return (1);
}

void	lock_forks(int number, t_data *data)
{
	int	i;

	i = number;
	sem_wait(data->sem);
	sem_wait(data->write);
	display_message(data, number, "has taken a fork");
	sem_post(data->write);
	sem_wait(data->sem);
	sem_wait(data->write);
	display_message(data, number, "has taken a fork");
	sem_post(data->write);
}

void	release_forks(t_data *data)
{
	sem_post(data->sem);
	sem_post(data->sem);
}
