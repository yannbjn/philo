/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:41:03 by yabejani          #+#    #+#             */
/*   Updated: 2024/05/01 15:59:02 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_ate(t_philo *tabphilo)
{
	int	i;
	int	philosatisfied;
	
	i = -1;
	philosatisfied = 0;
	if (tabphilo[0].nb_times_to_eat == -1)
		return (0);
	while (++i < tabphilo[0].nb_of_philo)
	{
		pthread_mutex_lock(tabphilo->meal_lock);
		if (tabphilo[i].meals_eaten == tabphilo[1].nb_times_to_eat)
			philosatisfied++;
		pthread_mutex_unlock(tabphilo->meal_lock);	
	}
	if (philosatisfied == tabphilo[0].nb_of_philo)
	{
		pthread_mutex_lock(tabphilo[0].dead_lock);
		*tabphilo->dead = 1;
		pthread_mutex_unlock(tabphilo[0].dead_lock);
		return (1);
	}
	return (0);
}

int	philo_death(t_philo *tabphilo, size_t time_to_die)
{
	pthread_mutex_lock(tabphilo->meal_lock);
	if (ft_get_time() - tabphilo->last_meal >= time_to_die && tabphilo->eating == 0)
	{
		pthread_mutex_unlock(tabphilo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(tabphilo->meal_lock);
	return (0);
}

int	check_dead(t_philo *tabphilo)
{
	int	i;

	i = -1;
	while (++i < tabphilo[0].nb_of_philo)
	{
		if (philo_death(&tabphilo[i], tabphilo[i].time_to_die))
		{
			print_action("died", &tabphilo[i], tabphilo[i].id);
			pthread_mutex_lock(tabphilo[0].dead_lock);
			*tabphilo->dead = 1;
			pthread_mutex_unlock(tabphilo[0].dead_lock);
			return (1);
		}
	}
	return (0);
}

void	*check(void *pointer)
{
	t_philo	*tabphilo;

	tabphilo = (t_philo *)pointer;
	while (1)
		if (check_dead(tabphilo) == 1 || check_if_ate(tabphilo) == 1)
			break ;
	return (pointer);
}
