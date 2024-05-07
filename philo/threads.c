/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:24:09 by yabejani          #+#    #+#             */
/*   Updated: 2024/05/07 12:13:03 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy(char *str, t_prog *prog, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&prog->write_lock);
	pthread_mutex_destroy(&prog->meal_lock);
	pthread_mutex_destroy(&prog->dead_lock);
	while (++i < prog->tabphilo[0].nb_of_philo)
		pthread_mutex_destroy(&forks[i]);
}

int	launch_threads(t_prog *prog, pthread_mutex_t *forks)
{
	pthread_t	supervise;
	int			i;

	if (pthread_create(&supervise, NULL, &ft_check, prog->tabphilo) != 0)
		(ft_destroy(TDERROR, prog, forks), exit(1));
	i = -1;
	while (++i < prog->tabphilo[0].nb_of_philo)
	{
		if (pthread_create(&prog->tabphilo[i].t_id, NULL,
				&routine, &prog->tabphilo[i]) != 0)
			(ft_destroy(TDERROR, prog, forks), exit(1));
	}
	if (pthread_join(supervise, NULL) != 0)
		(ft_destroy(JOINERROR, prog, forks), exit(1));
	i = -1;
	while (++i < prog->tabphilo[0].nb_of_philo)
		if (pthread_join(prog->tabphilo[i].t_id, NULL) != 0)
			(ft_destroy(JOINERROR, prog, forks), exit(1));
	return (0);
}
