/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:19:44 by yabejani          #+#    #+#             */
/*   Updated: 2024/05/07 12:19:37 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo			tabphilo[200];
	pthread_mutex_t	forks[200];
	t_prog			prog;

	ft_check_args(argc, argv);
	ft_init_prog(&prog, tabphilo);
	ft_init_forks(forks, ft_atoi(argv[1]));
	ft_init_philo(argv, tabphilo, &prog, forks);
	launch_threads(&prog, forks);
	ft_destroy(NULL, &prog, forks);
	return (0);
}
