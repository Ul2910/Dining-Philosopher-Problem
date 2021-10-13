/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keleonor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 23:51:12 by keleonor          #+#    #+#             */
/*   Updated: 2021/07/29 23:51:14 by keleonor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char *argv[])
{
	if (argc < 5 || argc > 6 || check_if_digits(argc, argv) == -1)
	{
		write(2, "Error\nusage: ./philo number_of_philosophers time_", 49);
		write(2, "to_die_in_ms time_to_eat_in_ms time_to_sleep_in_ms ", 51);
		write(2, "[number_of_times_each_philosopher_must_eat]\n", 44);
		return (-1);
	}
	if (ft_atoi(argv[1]) == 0)
		return (-1);
	return (0);
}

int	fill_struct(t_philos *philos, t_forks *forks_str, char *argv[], int argc)
{
	int	i;

	forks_str->philos_num = ft_atoi(argv[1]);
	forks_str->ate = 0;
	forks_str->sim_stop = 0;
	if (get_mallocs(philos, forks_str) == -1)
		return (-1);
	i = -1;
	while (++i < forks_str->philos_num)
	{
		philos[i].die = ft_atoi(argv[2]);
		philos[i].eat = ft_atoi(argv[3]);
		philos[i].sleep = ft_atoi(argv[4]);
		philos[i].counter = i;
		philos[i].ms = 0;
		if (argc == 6)
			philos[i].eat_num = ft_atoi(argv[5]);
		else
			philos[i].eat_num = -1;
		if (philos[i].eat_num == 0)
			return (-2);
	}
	fill_struct_philo_hands(philos, forks_str);
	return (0);
}

void	fill_struct_philo_hands(t_philos *philos, t_forks *forks_str)
{
	int	i;

	i = -1;
	while (++i < forks_str->philos_num)
	{
		if (i % 2 == 0)
		{
			philos[i].r_hand = i;
			philos[i].l_hand = i - 1;
			if (philos[i].l_hand < 0)
				philos[i].l_hand = philos[i].l_hand + forks_str->philos_num;
		}
		else if (i % 2 == 1)
		{
			philos[i].l_hand = i;
			philos[i].r_hand = i - 1;
			if (philos[i].r_hand < 0)
				philos[i].r_hand = philos[i].r_hand + forks_str->philos_num;
		}
	}
}

int	get_mallocs(t_philos *philos, t_forks *forks_str)
{
	int	i;

	forks_str->fork_n = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* forks_str->philos_num);
	forks_str->locks = (int *)malloc(sizeof(int) * forks_str->philos_num);
	if (forks_str->fork_n == NULL || forks_str->locks == NULL)
	{
		errors("malloc has failed", philos, forks_str);
		return (-1);
	}
	memset(forks_str->locks, 0, forks_str->philos_num * 4);
	i = 0;
	while (i < forks_str->philos_num)
	{
		philos[i].forks = forks_str;
		i++;
	}
	return (0);
}
