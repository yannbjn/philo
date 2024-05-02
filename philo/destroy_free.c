/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:33:19 by yabejani          #+#    #+#             */
/*   Updated: 2024/05/02 18:03:38 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_forks(pthread_mutex_t *forks, int i)
{
	int	j;

	j = -1;
	while (++j <= i)
		pthread_mutex_destroy(&forks[j]);
	free(forks);
}

void	ft_destroyfree_all(t_args *args, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	if (args)
		pthread_mutex_destroy(&args->monitor_mutex);
	i = -1;
	if (forks)
	{
		while (++i < args->nb_of_philo)
		{
			pthread_mutex_destroy(&forks[i]);
			philos[i].l_fork = NULL;
			philos[i].r_fork = NULL;
		}
		free(forks);
		forks = NULL;
	}
	if (philos)
	{
		free(philos);
		philos = NULL;
	}
}

void	ft_exit_errmsg(t_args *args, t_philo *philos, pthread_mutex_t *forks, char *str)
{
	ft_destroyfree_all(args, philos, forks);
	write(2, str, ft_strlen(str));
	exit(1);
}
