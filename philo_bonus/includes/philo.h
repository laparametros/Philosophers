/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:39:57 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/10/07 09:16:29 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <signal.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <time.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>

typedef struct s_philosopher
{
	int			number;
	int			is_dead;
	long long	last_time;
	int			have_eaten;
}	t_philo;

typedef struct properties
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eating;
	sem_t			*is_dead;
	pthread_mutex_t	**sem_forks;
	struct timeval	tv;
	struct timeval	current_time;
	unsigned int	sum_time;
}	t_def_properties;

typedef struct arguments
{
	t_philo				*philosophers;
	t_def_properties	properties;
	sem_t				**forks;
	pthread_t			*dead_control;
	pid_t				**pid_list;
	sem_t				*taking;
}	t_args;

int					control_args(t_def_properties properties);
int					print_state(const char *state, t_args *arguments);
int					ft_atoi(const char *str);
int					ft_sleep(long long time, t_args arguments);
int					eat_philo(t_args *args);
int					sleep_philo(t_args *args);
int					think_philo(t_args *args);
sem_t				**forks_init(t_args *arg);
char				*ft_sprintf(int num);
void				set_fork(t_args *arg);
void				unlink_sems(t_args *argument);
void				left_forks(t_args *args);
void				*dead_func(void *x);
void				dead_philo(t_args *argument, struct timeval tv);
void				destroy_properties(t_args *argument);
void				children_init(t_args *argument);
void				*philosophy(void *arg);
void				free_error_state(t_args *argument);
void				philo_properties(t_args *argument,
						sem_t **forks);
long long			get_time2(t_args *arguments, struct timeval tv2);
long long			get_time(t_args *arguments);
t_def_properties	properties_init(char **argv, int argc);

#endif // !PHILO_H
