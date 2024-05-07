/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:41:03 by yabejani          #+#    #+#             */
/*   Updated: 2024/05/07 14:05:52 by yabejani         ###   ########.fr       */
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
		pthread_mutex_lock(tabphilo[i].meal_lock);
		if (tabphilo[i].meals_eaten >= tabphilo[i].nb_times_to_eat)
			philosatisfied++;
		pthread_mutex_unlock(tabphilo[i].meal_lock);
	}
	if (philosatisfied == tabphilo[0].nb_of_philo)
	{
		pthread_mutex_lock(tabphilo[0].dead_lock);
		printf(ATEMEALS"%d meals 👍\n", tabphilo[0].nb_times_to_eat);
		*tabphilo->deadflag = 1;
		pthread_mutex_unlock(tabphilo[0].dead_lock);
		return (1);
	}
	return (0);
}

int	philo_death(t_philo *tabphilo, size_t time_to_die)
{
	pthread_mutex_lock(tabphilo->meal_lock);
	if (ft_get_time() - tabphilo->last_meal >= time_to_die
		&& tabphilo->eatingflag == 0)
		return (pthread_mutex_unlock(tabphilo->meal_lock), 1);
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
			print_action(DEAD_MSG, &tabphilo[i], tabphilo[i].id);
			pthread_mutex_lock(tabphilo[0].dead_lock);
			*tabphilo->deadflag = 1;
			pthread_mutex_unlock(tabphilo[0].dead_lock);
			return (1);
		}
	}
	return (0);
}

void	*ft_check(void *pointer)
{
	t_philo	*tabphilo;

	tabphilo = (t_philo *)pointer;
	while (1)
		if (check_dead(tabphilo) == 1 || check_if_ate(tabphilo) == 1)
			break ;
	return (pointer);
}
