/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:33:46 by hkuyucu           #+#    #+#             */
/*   Updated: 2023/10/06 12:22:46 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	monitor_loop(t_philo *philo, t_rules *rules)
{
	int	full_philos;

	full_philos = 0;
	pthread_mutex_lock(&(philo->ate_mutex));
	while ((int)(timestamp(rules->start_clock) - philo->ate_at) < rules->ms_die
		&& full_philos < rules->num_phil)
	{
		pthread_mutex_unlock(&(philo->ate_mutex));
		if (philo->id == 1)
			full_philos = 0;
		pthread_mutex_lock(&(philo->ate_mutex));
		if (philo->max_eat == 0)
			full_philos++;
		pthread_mutex_unlock(&(philo->ate_mutex));
		philo = philo->next;
		usleep(10);
		pthread_mutex_lock(&(philo->ate_mutex));
	}
	pthread_mutex_unlock(&(philo->ate_mutex));
	if (full_philos != rules->num_phil)
		log_death(philo->id, rules);
	else
		log_death(philo->id * -1, rules);
}

void	log_death(int num, t_rules *rules)
{
	pthread_mutex_lock(rules->start_mutex);
	rules->death = num;
	pthread_mutex_unlock(rules->start_mutex);
}

t_philo	*set_table(t_rules *rules)
{
	int		i;
	t_philo	*head;
	t_philo	*philos;

	philos = make_philo(rules, 1);
	if (!philos)
		return (NULL);
	head = philos;
	i = 0;
	while (i < rules->num_phil - 1)
	{
		philos->next = make_philo(rules, i + 2);
		if (!philos->next)
			return (free_the_philos(philos));
		philos->next->prev = philos;
		philos = philos->next;
		philos->left = &philos->prev->fork;
		i++;
	}
	philos->next = head;
	head->prev = philos;
	head->left = &head->prev->fork;
	return (head);
}

int	create_threads(t_philo *philo, t_rules *rules)
{
	while (philo->id != rules->num_phil)
	{
		if (pthread_create(&(philo->thread_id), NULL, life_of_philo, philo))
			return (-1);
		philo = philo->next;
	}
	if (pthread_create(&(philo->thread_id), NULL, life_of_philo, philo))
		return (-1);
	return (0);
}
