/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:59:49 by yabejani          #+#    #+#             */
/*   Updated: 2024/05/07 14:06:46 by yabejani         ###   ########.fr       */
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

# define NBARGS "Invalid number of arguments : input should look like this \n\
./philo [nb_of_philo] [time_to_die] [time_to_eat]\
 [time_to_sleep] [nb_of_time_each_philo_must_eat]<--optional\n"

# define MERROR "❗Malloc error❗\n"
# define MUTEXERR "❗Failed mutex❗\n"
# define TDERROR "❗Failed creting thread❗\n"
# define JOINERROR "❗Failed joining threads❗\n"	

# define DEAD_MSG "is dead 😵😱💀"
# define EAT_MSG "is eating 😋"
# define THINK_MSG "is thinking 🤓"
# define SLEEP_MSG "is sleeping 😴💤🛌"
# define FORK_MSG "has taken a fork 🍴"
# define ATEMEALS "All philos ate their "

typedef struct s_philo
{
	pthread_t		t_id;
	int				id;
	int				eatingflag;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				nb_of_philo;
	int				nb_times_to_eat;
	int				*deadflag;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*tabphilo;
}					t_prog;

int		main(int argc, char **argv);
void	ft_check_args(int argc, char **argv);
int		check_digit(char *str);
int		ft_atoi(char *str);
int		ft_strlen(char *str);

void	ft_init_forks(pthread_mutex_t *forks, int philonbr);
void	ft_init_prog(t_prog *prog, t_philo *tabphilo);
void	ft_init_philo(char **argv, t_philo *tabphilo,
			t_prog *prog, pthread_mutex_t *forks);
size_t	ft_get_time(void);
int		ft_usleep(size_t ms);
void	print_action(char *str, t_philo *tabphilo, int id);

int		launch_threads(t_prog *prog, pthread_mutex_t *forks);
void	ft_destroy(char *str, t_prog *prog, pthread_mutex_t *forks);

void	*ft_check(void *pointer);
int		check_dead(t_philo *tabphilo);
int		check_deadflag(t_philo *philo);
int		philo_death(t_philo *tabphilo, size_t time_to_die);
int		check_if_ate(t_philo *tabphilo);

void	*routine(void *pointer);

#endif