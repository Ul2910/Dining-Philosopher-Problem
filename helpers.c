/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keleonor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 23:50:15 by keleonor          #+#    #+#             */
/*   Updated: 2021/07/29 23:50:27 by keleonor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *nptr)
{
	int	i;
	int	number;

	i = 0;
	number = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + (nptr[i] - 48);
		i++;
	}
	return (number);
}

int	check_if_digits(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void	errors(char *error, t_philos *philos, t_forks *forks_str)
{
	write(2, "Error\n", 6);
	write(2, error, ft_strlen(error));
	ft_free(philos, forks_str);
}

void	ft_free(t_philos *philos, t_forks *forks_str)
{
	if (philos)
		free(philos);
	if (forks_str->fork_n)
		free(forks_str->fork_n);
	if (forks_str->locks)
		free(forks_str->locks);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
