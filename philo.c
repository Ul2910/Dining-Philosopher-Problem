/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keleonor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 23:50:53 by keleonor          #+#    #+#             */
/*   Updated: 2021/07/29 23:50:56 by keleonor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philos	*philos;
	t_forks		forks_str;

	if (check_args(argc, argv) == -1)
		return (-1);
	philos = (t_philos *)malloc(sizeof(t_philos) * ft_atoi(argv[1]));
	if (philos == NULL)
	{
		errors("malloc has failed", philos, &forks_str);
		return (-1);
	}
	if (fill_struct(philos, &forks_str, argv, argc) == 0)
	{
		if (init_mutexes(philos, &forks_str) == -1
			|| create_threads(philos, &forks_str) == -1)
			return (-1);
		join(philos, &forks_str);
		destroy(philos, &forks_str);
	}
	ft_free(philos, &forks_str);
	return (0);
}

int	init_mutexes(t_philos *philos, t_forks *forks_str)
{
	int	i;

	i = -1;
	while (++i < forks_str->philos_num)
	{
		if (pthread_mutex_init(&(forks_str->fork_n[i]), NULL) != 0)
		{
			while (--i > -1)
				pthread_mutex_destroy(&(forks_str->fork_n[i]));
			errors("mutex init has failed", philos, forks_str);
			return (-1);
		}
	}
	if (pthread_mutex_init(&(forks_str->print), NULL) != 0)
	{
		i = -1;
		while (++i < forks_str->philos_num)
			pthread_mutex_destroy(&(forks_str->fork_n[i]));
		errors("mutex init has failed", philos, forks_str);
		return (-1);
	}
	return (0);
}

int	create_threads(t_philos *philos, t_forks *forks_str)
{
	int	i;

	i = -1;
	forks_str->start_sim = 0;
	if (get_start_time(philos, forks_str) != 0)
	{
		destroy(philos, forks_str);
		ft_free(philos, forks_str);
		return (-1);
	}
	while (++i < forks_str->philos_num)
	{
		philos[i].death_time = philos->die;
		if (pthread_create(&(philos[i].philo), NULL, &cycle_of_life,
				(void *)&(philos[i])) != 0)
		{
			destroy(philos, forks_str);
			errors("thread creation has failed", philos, forks_str);
			return (-1);
		}
	}
	forks_str->start_sim = 1;
	return (0);
}

void	join(t_philos *philos, t_forks *forks_str)
{
	int	i;

	i = 0;
	while (i < forks_str->philos_num)
	{
		if (pthread_join(philos[i].philo, NULL) != 0)
			write(2, "Error\npthread_join has failed\n", 30);
		i++;
	}
}

void	destroy(t_philos *philos, t_forks *forks_str)
{
	int	i;

	i = 0;
	while (i < forks_str->philos_num)
	{
		if (forks_str->locks[i] == -1)
		{
			pthread_mutex_unlock(&(forks_str->fork_n[i]));
			forks_str->locks[i] = 0;
		}
		if (pthread_mutex_destroy(&(forks_str->fork_n[i])) != 0)
			write(2, "Error\nmutex_destroy has failed\n", 31);
		i++;
	}
	if (pthread_mutex_destroy(&(forks_str->print)) != 0)
		write(2, "Error\nmutex_destroy has failed\n", 31);
	(void)philos;
}
