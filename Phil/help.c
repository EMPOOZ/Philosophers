/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tconwy <tconwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:32:16 by tconwy            #+#    #+#             */
/*   Updated: 2022/02/25 14:35:14 by tconwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	c;

	if (fd < 0)
		return ;
	if (s == NULL)
		return ;
	c = 0;
	while (s[c])
	{
		write(fd, &s[c], 1);
		c++;
	}
}

int	ft_atoi(const char *str)
{
	long long		c;
	long long		f;
	unsigned int	m;

	f = 0;
	c = 1;
	m = 0;
	while (str[f] == '\t' || str[f] == '\n' || str[f] == '\v'
		|| str[f] == '\f' || str[f] == '\r' || str[f] == ' ')
		f++;
	if (str[f] == '+' || str[f] == '-')
		if (str[f++] == '-')
			c *= -1;
	while ((str[f] >= '0') && (str[f] <= '9'))
		m = (m * 10) + (str[f++] - '0');
	c *= m;
	if (c >= 2147483648)
		return (-1);
	if (c <= -2147483649)
		return (0);
	return (c);
}

int	sleep2(useconds_t n_milliseconds)
{
	useconds_t		before;
	useconds_t		after;

	before = get_total_time();
	after = before;
	while (after - before < n_milliseconds)
	{
		if (usleep(500) == -1)
			return (-1);
		after = get_total_time();
	}
	return (0);
}
