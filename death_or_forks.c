/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_or_forks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keleonor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 02:08:35 by keleonor          #+#    #+#             */
/*   Updated: 2021/07/30 02:08:38 by keleonor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_or_right_fork_waiting(t_philos *philos)
{
	while (philos->forks->sim_stop != 1)
	{
		usleep(50);
		if (check_if_dead(philos) == -1)
		{
			get_time(philos);
			pthread_mutex_lock(&(philos->forks->print));
			if (philos->forks->sim_stop == 0)
				printf("%li %d died\n", philos->ms, philos->counter + 1);
			philos->forks->sim_stop = 1;
			pthread_mutex_unlock(&(philos->forks->print));
			return ;
		}
		if (philos->forks->locks[philos->r_hand] == 0)
			return ;
	}
}

void	death_or_left_fork_waiting(t_philos *philos)
{
	while (philos->forks->sim_stop != 1)
	{
		usleep(50);
		if (check_if_dead(philos) == -1)
		{
			get_time(philos);
			pthread_mutex_lock(&(philos->forks->print));
			if (philos->forks->sim_stop == 0)
				printf("%li %d died\n", philos->ms, philos->counter + 1);
			philos->forks->sim_stop = 1;
			pthread_mutex_unlock(&(philos->forks->print));
			return ;
		}
		if (philos->forks->locks[philos->l_hand] == 0)
			return ;
	}
}

int	take_right_fork(t_philos *philos)
{
	philos->forks->locks[philos->r_hand] = -1;
	pthread_mutex_lock(&(philos->forks->fork_n[philos->r_hand]));
	pthread_mutex_lock(&(philos->forks->print));
	get_time(philos);
	if (philos->forks->sim_stop == 0)
		printf("%li %d has taken a fork\n", philos->ms, philos->counter + 1);
	else
	{
		pthread_mutex_unlock(&(philos->forks->print));
		return (-1);
	}
	pthread_mutex_unlock(&(philos->forks->print));
	return (0);
}

int	take_left_fork(t_philos *philos)
{
	pthread_mutex_lock(&(philos->forks->fork_n[philos->l_hand]));
	philos->forks->locks[philos->l_hand] = -1;
	pthread_mutex_lock(&(philos->forks->print));
	get_time(philos);
	if (philos->forks->sim_stop == 0)
		printf("%li %d has taken a fork\n", philos->ms, philos->counter + 1);
	else
	{
		pthread_mutex_unlock(&(philos->forks->print));
		return (-1);
	}
	pthread_mutex_unlock(&(philos->forks->print));
	return (0);
}

void	put_forks(t_philos *philos)
{
	pthread_mutex_unlock(&(philos->forks->fork_n[philos->r_hand]));
	pthread_mutex_unlock(&(philos->forks->fork_n[philos->l_hand]));
	philos->forks->locks[philos->r_hand] = 0;
	philos->forks->locks[philos->l_hand] = 0;
}
