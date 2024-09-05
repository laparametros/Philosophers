/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:23:53 by hkuyucu           #+#    #+#             */
/*   Updated: 2023/10/06 12:21:53 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_up(t_philo *philo, t_rules *rules, int i, unsigned long time)
{
	t_philo	*next;

	while (i < rules->num_phil)
	{
		pthread_join(philo->thread_id, NULL);
		philo = philo->next;
		i++;
	}
	i = 0;
	while (i < rules->num_phil)
	{
		if (philo->id < rules->num_phil)
			next = philo->next;
		else
			next = NULL;
		pthread_mutex_destroy(&philo->ate_mutex);
		pthread_mutex_destroy(&philo->fork);
		free(philo);
		if (next)
			philo = next;
		i++;
	}
	if (rules->death > 0)
		printf("%lu %d died\n", time, rules->death);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_rules			rules;
	pthread_mutex_t	start;

	rules.start_mutex = &start;
	gettimeofday(&(rules.start_clock), NULL);
	if (parse_input(argc, argv, &rules) < 0)
		return (0);
	philo = set_table(&rules);
	if (!philo)
		return (1);
	rules.start_ms = timestamp(rules.start_clock);
	pthread_mutex_init(rules.start_mutex, NULL);
	pthread_mutex_lock(rules.start_mutex);
	if (create_threads(philo, &rules) < 0)
		return (1);
	pthread_mutex_unlock(rules.start_mutex);
	monitor_loop(philo, &rules);
	clean_up(philo, &rules, 0, timestamp(rules.start_clock));
	return (0);
}
