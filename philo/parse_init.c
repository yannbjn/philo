/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:50:49 by yabejani          #+#    #+#             */
/*   Updated: 2024/05/02 17:43:32 by yabejani         ###   ########.fr       */
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

void	ft_parse_input(t_args *args, int argc, char **argv)
{
	args->nb_of_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->nb_meals_to_eat = -1;
	if (argc = 6)
		args->nb_meals_to_eat = ft_atoi(argv[5]);
	args->flag_end = false;
}

pthread_mutex_t	*ft_init_forks(t_args *args)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * (args->nb_of_philo));
	if (!forks)
		(write(2, MERROR, 20), exit(1));
	i = -1;
	while (++i < args->nb_of_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			ft_free_forks(forks, i);
			(write(2, MUTEXERR, 20), exit(1));
		}
	}
	return (forks);
}

t_philo	*ft_init_philos(t_args  *args, pthread_mutex_t *forks)
{
	int		i;
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * (args->nb_of_philo));
	if (!philos)
		(write(2, MERROR, 20), ft_free_forks(forks), exit(1));
	i = -1;
	while (++i < args->nb_of_philo)
	{
		philos[i].id_philo = i + 1;
		philos[i].meal_eaten = 0;
		philos[i].last_meal_time = ft_get_time();
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % args->nb_of_philo];
		philos[i].args = args;
	}
	return (philos);
}
