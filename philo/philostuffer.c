/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philostuffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:35:31 by hkuyucu           #+#    #+#             */
/*   Updated: 2023/10/06 14:38:10 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*make_philo(t_rules *rules, int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->rules = rules;
	philo->max_eat = rules->max_eat;
	philo->ate_at = 0;
	philo->next = NULL;
	philo->prev = NULL;
	if (pthread_mutex_init(&philo->fork, NULL)
		|| pthread_mutex_init(&philo->ate_mutex, NULL))
	{
		free(philo);
		return (NULL);
	}
	philo->right = &philo->fork;
	return (philo);
}

void	*life_of_philo(void *args)
{
	t_philo	*philo;
	t_rules	rules;

	philo = (t_philo *)args;
	rules = *(philo->rules);
	pthread_mutex_lock(rules.start_mutex);
	pthread_mutex_unlock(rules.start_mutex);
	if (philo->id & 1)
		ms_sleep(5);
	while (1)
	{
		eat(philo);
		if (print_action("is sleeping", philo) < 0)
			break ;
		ms_sleep(rules.ms_sleep);
		if (print_action("is thinking", philo) < 0)
			break ;
		ms_sleep(1);
	}
	return (NULL);
}

int	get_forks(t_philo *philo)
{
	struct timeval	start_clock;

	start_clock = philo->rules->start_clock;
	if (philo->id & 1)
	{
		pthread_mutex_lock(philo->left);
		print_action("has taken a fork", philo);
		if (philo->rules->num_phil == 1)
		{
			pthread_mutex_unlock(philo->left);
			ms_sleep(philo->rules->ms_die);
		}
		pthread_mutex_lock(philo->right);
		print_action("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->right);
		print_action("has taken a fork", philo);
		pthread_mutex_lock(philo->left);
		print_action("has taken a fork", philo);
	}
	return (0);
}

void	eat(t_philo *philo)
{
	t_rules	rules;

	rules = *(philo->rules);
	get_forks(philo);
	if (print_action("is eating", philo) < 0)
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		return ;
	}
	pthread_mutex_lock(&(philo->ate_mutex));
	philo->ate_at = timestamp(rules.start_clock);
	pthread_mutex_unlock(&(philo->ate_mutex));
	ms_sleep(rules.ms_eat);
	pthread_mutex_lock(&(philo->ate_mutex));
	if (philo->max_eat > 0)
		philo->max_eat--;
	pthread_mutex_unlock(&(philo->ate_mutex));
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}
