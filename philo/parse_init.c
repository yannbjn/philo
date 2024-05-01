/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:50:49 by yabejani          #+#    #+#             */
/*   Updated: 2024/05/01 15:28:29 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		(write(2, NBARGS, 170), exit(1));
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200 || check_digit(argv[1]))
		(write(2, "Invalid number of Philo\n", 25), exit(1));
	if (ft_atoi(argv[2]) <= 0 || check_digits(argv[2]))
		(write(2, "Invalide time_to_die\n", 22), exit(1));
	if (ft_atoi(argv[3]) <= 0 || check_digits(argv[3]))
		(write(2, "Invalid time_to_eat\n", 21), exit(1));
	if (ft_atoi(argv[4] <= 0) || check_digits(argv[4]))
		(write(2, "Invalid time_to_sleep\n", 23), exit(1));
	if (argc == 6)
		if (ft_atoi(argv[5] <= 0) || check_digits(argv[5]))
			(write(2, "Invalid nb of time each philo must eat\n", 40), exit(1));
}

void	ft_init_forks(pthread_mutex_t *forks, int philonbr)
{
	int	i;

	i = -1;
	while (++i < philonbr)
		pthread_mutex_init(&forks[i], NULL);
}

void	ft_init_prog(t_prog *prog, t_philo *tabphilo)
{
	prog->dead_flag = 0;
	prog->tabphilo = tabphilo;
	pthread_mutex_init(&prog->write_lock, NULL);
	pthread_mutex_init(&prog->dead_lock, NULL);
	pthread_mutex_init(&prog->meal_lock, NULL);
}

static void	ft_init_input(char **argv, t_philo *philo)
{
	philo->nb_of_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->nb_times_to_eat = 0;
	if (argv[5])
		philo->nb_times_to_eat = ft_atoi(argv[5]);
}

void	ft_init_philo(char **argv, t_philo *tabphilo,
t_prog *prog, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		tabphilo[i].id = i + 1;
		tabphilo[i].eating = 0;
		tabphilo[i].meals_eaten = 0;
		ft_init_input(argv, &tabphilo[i]);
		tabphilo[i].start_time = ft_get_time();
		tabphilo[i].last_meal = ft_get_time();
		tabphilo[i].write_lock = &prog->write_lock;
		tabphilo[i].dead_lock = &prog->dead_lock;
		tabphilo[i].meal_lock = &prog->meal_lock;
		tabphilo[i].dead = &prog->dead_flag;
		tabphilo[i].l_fork = &forks[i];
		if (i == 0)
			tabphilo[i].r_fork = &forks[tabphilo[i].nb_of_philo - 1];
		else
			tabphilo[i].r_fork = &forks[i - 1];
		i++;
	}
}
