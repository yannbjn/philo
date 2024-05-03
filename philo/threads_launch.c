/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_launch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:17:16 by yabejani          #+#    #+#             */
/*   Updated: 2024/05/03 16:45:41 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitoring(t_philo *philos, t_eventid event_id)
{
	size_t	timestamp;
	const char	*events[6] = {DEAD_MSG, EAT_MSG, THINK_MSG,
		SLEEP_MSG, FORK_MSG, DROP_MSG};

	pthread_mutex_lock(&philos->args->monitor_mutex);
	if (philos->args->flag_end)
	{
		pthread_mutex_unlock(&philos->args->monitor_mutex);
		return ;
	}
	timestamp = get_time() - philos->start_time;
	printf("%zu %d %s", timestamp, philos->id_philo, events[event_id]);
	pthread_mutex_unlock(&philos->args->monitor_mutex);
}

static void	all_satisfied(t_args *args)
{
	args->flag_end = true;
	printf("Every Philosopher had %d meals!👍😋\n", args->nb_meals_to_eat);
	pthread_mutex_unlock(&args->monitor_mutex);
}

static bool	check_if_dead(t_args *args, t_philo *philos, int *satisfied_philos)
{
	if (args->nb_meals_to_eat > 0
		&& philos->meal_eaten >= args->nb_meals_to_eat)
		*satisfied_philos++;
	if (ft_get_time() - philos->last_meal_time >= philos->args->time_to_die)
	{
		pthread_mutex_unlock(&args->monitor_mutex);
		monitoring(philos, DEAD);
		pthread_mutex_lock(&args->monitor_mutex);
		args->flag_end = true;
		pthread_mutex_unlock(&args->monitor_mutex);
		return (true);
	}
	return (false);
}

static void	ft_monitor(t_philo *philos, t_args *args)
{
	int	satisfied_philos;
	int	i;

	satisfied_philos = 0;
	while (true)
	{
		i = -1;
		pthread_mutex_lock(&args->monitor_mutex);
		while (++i < args->nb_of_philo)
		{
			if (check_if_dead(args, &philos[i], &satisfied_philos))
				return ;
		}
		if (satisfied_philos == args->nb_of_philo)
			return (all_satisfied(args));
		pthread_mutex_unlock(&args->monitor_mutex);
	}
}

void	ft_launch_threads(t_args *args, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < args->nb_of_philo)
	{
		philos[i].start_time = ft_get_time();
		if (pthread_create(&philos[i].t_id, NULL, routine,
				(void *)&philos[i]) != 0)
			ft_exit_errmsg(args, philos, forks, TDERROR);
	}
	monitor(philos, args);
	i = -1;
	while (++i < args->nb_of_philo)
	{
		if (pthread_join(&philos[i].t_id, NULL) != 0)
			ft_exit_errmsg(args, philos, forks, JOINERROR);
	}
}
