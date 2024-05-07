/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:24:19 by yabejani          #+#    #+#             */
/*   Updated: 2024/05/07 12:09:26 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_deadflag(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->deadflag == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

static void	ft_sleep(t_philo *philo)
{
	print_action(SLEEP_MSG, philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

static void	ft_think(t_philo *philo)
{
	print_action(THINK_MSG, philo, philo->id);
}

static void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_action(FORK_MSG, philo, philo->id);
	if (philo->nb_of_philo == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_action(FORK_MSG, philo, philo->id);
	philo->eatingflag = 1;
	print_action(EAT_MSG, philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = ft_get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eatingflag = 0;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!check_deadflag(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (pointer);
}
