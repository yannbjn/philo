/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:59:49 by yabejani          #+#    #+#             */
/*   Updated: 2024/05/03 16:44:13 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

# define NBARGS "Invalid number of arguments : input should look like this \n\
./philo [nb_of_philo] [time_to_die] [time_to_eat]\
 [time_to_sleep] [nb_of_time_each_philo_must_eat]<--optional\n"

# define MERROR "❗Malloc error❗\n"
# define MUTEXERR "❗Failed mutex❗\n"
# define TDERROR "❗Failed creting thread❗\n"
# define JOINERROR "❗Failed joining threads❗\n"

# define DEAD_MSG "is dead 😵😱\n"
# define EAT_MSG "is eating 😋\n"
# define THINK_MSG "is thinking 🤓\n"
# define SLEEP_MSG "is sleeping 😴💤🛌\n"
# define FORK_MSG "has taken a fork 🍴\n"
# define DROP_MSG "has dropped a fork 🍴💥\n"

typedef struct s_args
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals_to_eat;
	bool			flag_end;
	pthread_mutex_t	monitor_mutex;
}					t_args;

typedef struct s_philo
{
	int				id_philo;
	int				meal_eaten;
	size_t			start_time;
	size_t			last_meal_time;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_args			*args;
	pthread_t		t_id;
}					t_philo;

typedef enum e_eventid
{
	DEAD,
	EAT,
	THINK,
	SLEEP,
	FORK,
	DROP,
}			t_eventid;

void			ft_check_args(int argc, char **argv);
int				check_digit(char *str);
int				ft_atoi(char *str);

size_t			ft_get_time(void);
int				ft_usleep(size_t ms);

void			ft_parse_input(t_args *args, int argc, char **argv);
pthread_mutex_t	*ft_init_forks(t_args *args);
t_philo			*ft_init_philos(t_args  *args, pthread_mutex_t *forks);

void			*routine(void *_philo);
void			ft_exit_errmsg(t_args *args, t_philo *philos, pthread_mutex_t *forks, char *str);

#endif