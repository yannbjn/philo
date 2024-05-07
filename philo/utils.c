/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:04:34 by yabejani          #+#    #+#             */
/*   Updated: 2024/05/07 13:58:33 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) && str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = 10 * res + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

int	check_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (1);
	return (0);
}

size_t	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < ms)
		usleep(500);
	return (0);
}

void	print_action(char *str, t_philo *tabphilo, int id)
{
	size_t	time;

	pthread_mutex_lock(tabphilo->write_lock);
	time = ft_get_time() - tabphilo->start_time;
	if (!check_deadflag(tabphilo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(tabphilo->write_lock);
}
