/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tconwy <tconwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:32:31 by tconwy            #+#    #+#             */
/*   Updated: 2022/02/27 12:11:53 by tconwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIL_H
# define PHIL_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_phil
{
	pthread_t			thread;
	int					index;
	int					eat_count;
	unsigned long long	time_last_eat;
	pthread_mutex_t		mutex;
	struct s_data		*data;
}						t_phil;

typedef struct s_data
{
	int					count_phil;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	time_to_start;
	int					count_eat;
	t_phil				*phil;
	bool				dead;
}						t_data;

int					data_init(t_data *data, int argc, char **argv);
void				display_message(t_data *data, int number, char *str_err);
unsigned long long	get_time(t_data *data);
void				release_forks(int number, t_data *data);
void				lock_forks(int number, t_data *data);
void				monitor(t_data *data);
void				free_data(t_data *data);
int					check_arg(int argc, char **argv);
void				free_data(t_data *data);
void				ft_putstr_fd(char *s, int fd);
int					ft_atoi(const char *str);
int					sleep2(useconds_t n_milliseconds);
int					ft_printf(const char *string, ...);
unsigned long long	get_total_time(void);

#endif