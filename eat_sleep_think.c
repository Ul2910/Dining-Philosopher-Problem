/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keleonor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 02:08:45 by keleonor          #+#    #+#             */
/*   Updated: 2021/07/30 02:08:47 by keleonor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_eating(t_philos *philos)
{
	pthread_mutex_lock(&(philos->forks->print));
	get_time(philos);
	if (philos->forks->sim_stop == 0)
		printf("%li %d is eating\n", philos->ms, philos->counter + 1);
	else
	{
		pthread_mutex_unlock(&(philos->forks->print));
		return (-1);
	}
	philos->death_time = philos->ms + philos->die;
	pthread_mutex_unlock(&(philos->forks->print));
	return (0);
}

int	print_sleeping(t_philos *philos)
{
	pthread_mutex_lock(&(philos->forks->print));
	get_time(philos);
	if (philos->forks->sim_stop == 0)
		printf("%li %d is sleeping\n", philos->ms, philos->counter + 1);
	else
	{
		pthread_mutex_unlock(&(philos->forks->print));
		return (-1);
	}
	pthread_mutex_unlock(&(philos->forks->print));
	return (0);
}

int	print_thinking(t_philos *philos)
{
	pthread_mutex_lock(&(philos->forks->print));
	get_time(philos);
	if (philos->forks->sim_stop == 0)
		printf("%li %d is thinking\n", philos->ms, philos->counter + 1);
	else
	{
		pthread_mutex_unlock(&(philos->forks->print));
		return (-1);
	}
	pthread_mutex_unlock(&(philos->forks->print));
	return (0);
}

int	eating(t_philos *philos)
{
	if (philos->death_time >= philos->ms + philos->eat)
	{
		my_usleep(philos->eat * 1000, philos);
		philos->eat_num--;
		if (philos->eat_num == 0)
			philos->forks->ate++;
		if (philos->forks->ate >= philos->forks->philos_num)
		{
			philos->forks->sim_stop = 1;
			return (-1);
		}
	}
	else
	{
		my_usleep((philos->death_time - philos->ms + 1) * 1000, philos);
		pthread_mutex_lock(&(philos->forks->print));
		get_time(philos);
		if (philos->forks->sim_stop == 0)
			printf("%li %d died\n", philos->ms, philos->counter + 1);
		philos->forks->sim_stop = 1;
		pthread_mutex_unlock(&(philos->forks->print));
		return (-1);
	}
	return (0);
}

int	sleeping(t_philos *philos)
{
	if (philos->death_time >= philos->ms + philos->sleep)
		my_usleep(philos->sleep * 1000, philos);
	else
	{
		my_usleep((philos->death_time - philos->ms + 1) * 1000, philos);
		pthread_mutex_lock(&(philos->forks->print));
		get_time(philos);
		if (philos->forks->sim_stop == 0)
			printf("%li %d died\n", philos->ms, philos->counter + 1);
		philos->forks->sim_stop = 1;
		pthread_mutex_unlock(&(philos->forks->print));
		return (-1);
	}
	return (0);
}
