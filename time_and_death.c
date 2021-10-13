/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_and_death.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keleonor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 23:51:21 by keleonor          #+#    #+#             */
/*   Updated: 2021/07/29 23:51:24 by keleonor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_start_time(t_philos *philos, t_forks *forks_str)
{
	if (gettimeofday(&(philos[0].s_time), NULL) != 0)
	{
		write(2, "Error\ngettimeofday has failed\n", 30);
		return (-1);
	}
	forks_str->start_usec = philos[0].s_time.tv_usec;
	forks_str->start_sec = philos[0].s_time.tv_sec;
	return (0);
}

int	check_if_dead(t_philos *philos)
{
	get_time(philos);
	if (philos->ms > philos->death_time)
		return (-1);
	return (0);
}

void	get_time(t_philos *philos)
{
	gettimeofday(&philos->s_time, NULL);
	philos->ms = ((((philos->s_time.tv_sec - philos->forks->start_sec)
					* 1000000 + philos->s_time.tv_usec)
				   - philos->forks->start_usec) * 0.001);
}

void	my_usleep(int time, t_philos *philos)
{
	int	time_stop;

	get_time(philos);
	time_stop = philos->ms + time * 0.001;
	while (philos->ms < time_stop)
	{
		usleep(100);
		get_time(philos);
	}
	return ;
}
