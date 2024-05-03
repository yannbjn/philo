/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:24:19 by yabejani          #+#    #+#             */
/*   Updated: 2024/05/03 17:00:51 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_eat(t_philo *philos)
{
	pick_forks(philos);
	pthread_mutex_lock(&philos->args->monitor_mutex);
	philos->last_meal_time = ft_get_time();
	philos->meal_eaten += 1;
	pthread_mutex_unlock(&philos->args->monitor_mutex);
	monitoring(philos, EAT);
	
}

void	*routine(void *_philo)
{
	t_philo	*philos;

	philos = (t_philo *)_philo;
	if (philos->args->nb_of_philo == 1)
		return (monitoring(philos, FORK), NULL);
	while (1)
	{
		pthread_mutex_lock(&philos->args->monitor_mutex);
		if (philos->args->flag_end)
		{
			pthread_mutex_unlock(&philos->args->monitor_mutex);
			break ;
		}
		pthread_mutex_unlock(&philos->args->monitor_mutex);
		ft_eat(philos);
		ft_sleep(philos);
		monitoring(philos, THINK);
	}
	return (NULL);
}
