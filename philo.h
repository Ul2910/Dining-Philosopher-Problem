/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keleonor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 23:51:01 by keleonor          #+#    #+#             */
/*   Updated: 2021/07/29 23:51:03 by keleonor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_forks
{
	pthread_mutex_t	*fork_n;
	pthread_mutex_t	print;
	int				start_sim;
	int				*locks;
	int				philos_num;
	int				ate;
	int				sim_stop;
	long int		start_usec;
	long int		start_sec;
}	t_forks;

typedef struct s_philos
{
	pthread_t		philo;
	t_forks			*forks;
	int				counter;
	int				l_hand;
	int				r_hand;
	int				die;
	int				eat;
	int				sleep;
	int				eat_num;
	int				death_time;
	struct timeval	s_time;
	long int		ms;
}	t_philos;

int		init_mutexes(t_philos *philos, t_forks *forks_str);
int		create_threads(t_philos *philos, t_forks *forks_str);
void	join(t_philos *philos, t_forks *forks_str);
void	destroy(t_philos *philos, t_forks *forks_str);

int		check_args(int argc, char *argv[]);
int		fill_struct(t_philos *philos, t_forks *forks_str, char *argv[],
			int argc);
void	fill_struct_philo_hands(t_philos *philos, t_forks *forks_str);
int		get_mallocs(t_philos *philos, t_forks *forks_str);

int		get_start_time(t_philos *philos, t_forks *forks_str);
int		check_if_dead(t_philos *philos);
void	get_time(t_philos *philos);
void	my_usleep(int time, t_philos *philos);

int		ft_atoi(char *nptr);
int		check_if_digits(int argc, char *argv[]);
void	errors(char *error, t_philos *philos, t_forks *forks_str);
void	ft_free(t_philos *philos, t_forks *forks_str);
int		ft_strlen(char *str);

void	*cycle_of_life(void *arg);
void	the_only_philo(t_philos *philos);

void	death_or_right_fork_waiting(t_philos *philos);
void	death_or_left_fork_waiting(t_philos *philos);
void	put_forks(t_philos *philos);
int		take_right_fork(t_philos *philos);
int		take_left_fork(t_philos *philos);

int		print_eating(t_philos *philos);
int		print_sleeping(t_philos *philos);
int		print_thinking(t_philos *philos);
int		eating(t_philos *philos);
int		sleeping(t_philos *philos);

#endif
