/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:19:44 by yabejani          #+#    #+#             */
/*   Updated: 2024/05/02 17:14:32 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	t_args			args;

	ft_check_args(argc, argv);
	ft_parse_input(&args, argc, argv);
	forks = ft_init_forks(&args);
	philos = ft_init_philos(&args, forks);
	
	return (0);
}
