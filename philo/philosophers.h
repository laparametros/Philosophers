/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:08:37 by hkuyucu           #+#    #+#             */
/*   Updated: 2023/10/06 12:22:30 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_rules
{
	int				num_phil;
	int				death;
	int				ms_die;
	int				ms_eat;
	int				ms_sleep;
	int				max_eat;
	long			start_ms;
	pthread_mutex_t	*start_mutex;
	struct timeval	start_clock;
}	t_rules;

typedef struct s_philo
{
	int				id;
	t_rules			*rules;
	int				max_eat;
	long			ate_at;
	pthread_mutex_t	fork;
	pthread_mutex_t	ate_mutex;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_t		thread_id;
	struct s_philo	*next;
	struct s_philo	*prev;
}	t_philo;

//simulation.c
void			monitor_loop(t_philo *philo, t_rules *rules);
void			log_death(int num, t_rules *rules);
t_philo			*set_table(t_rules *rules);
int				create_threads(t_philo *philo, t_rules *rules);

//philostuffer.c
int				print_action(char *action, t_philo *philo);
t_philo			*make_philo(t_rules *rules, int id);
void			*free_the_philos(t_philo *philo);
void			*life_of_philo(void *args);
int				get_forks(t_philo *philo);
void			eat(t_philo *philo);

//input.c
int				atoi_philo(const char *str);
int				parse_input(int argc, char **argv, t_rules *rules);

//time.c
unsigned long	timestamp(struct timeval start_clock);
unsigned long	timeval_to_ms(struct timeval clock);
void			ms_sleep(int ms);

#endif
