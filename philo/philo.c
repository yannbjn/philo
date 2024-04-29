/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:19:44 by yabejani          #+#    #+#             */
/*   Updated: 2024/04/29 19:10:48 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo			tabphilo[200];
	pthread_mutex_t	forks[200];
	t_prog			prog;

	ft_check_args(argc, argv);
	ft_init_forks(forks, ft_atoi(argv[1]));
	ft_init_prog(tabphilo, &prog);
	ft_inits_philo(argc, argv, tabphilo, &prog, &forks);
	return (0);
}
