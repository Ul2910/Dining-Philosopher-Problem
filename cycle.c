/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keleonor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 23:51:33 by keleonor          #+#    #+#             */
/*   Updated: 2021/07/29 23:51:35 by keleonor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*cycle_of_life(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	while (philos->forks->start_sim != 1)
		;
	get_time(philos);
	if (philos->forks->philos_num == 1)
		the_only_philo(philos);
	while (philos->forks->philos_num > 1)
	{
		death_or_right_fork_waiting(philos);
		if (philos->forks->sim_stop == 1 || take_right_fork(philos) == -1)
			return (NULL);
		death_or_left_fork_waiting(philos);
		if (philos->forks->sim_stop == 1 || take_left_fork(philos) == -1)
			return (NULL);
		if (print_eating(philos) == -1 || eating(philos) == -1)
			return (NULL);
		put_forks(philos);
		if (print_sleeping(philos) == -1 || sleeping(philos) == -1)
			return (NULL);
		if (print_thinking(philos) == -1)
			return (NULL);
	}
	return (NULL);
}

void	the_only_philo(t_philos *philos)
{
	my_usleep((philos->die + 1) * 1000, philos);
	printf("%li %d died\n", philos->ms, philos->counter + 1);
}
