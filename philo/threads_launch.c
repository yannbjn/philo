/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_launch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:17:16 by yabejani          #+#    #+#             */
/*   Updated: 2024/05/02 18:24:57 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			if (is_philo_dead(args, &philos[i], &satisfied_philos))
				return ;
		}
		if (satisfied_philos == args->nb_of_philo)
			return (all_have_eaten(args));
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
		if (pthread_create(&philos[i].t_id, NULL, routine, (void *)&philos[i]) != 0)
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
