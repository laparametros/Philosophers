/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:34:45 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/10/05 15:07:08 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	dead_philo(t_args *argument, struct timeval tv)
{
	t_philo				*philosophers;
	long long			time;
	long long			time2;

	philosophers = argument->philosophers;
	time = get_time2(argument, tv);
	sem_wait(argument->taking);
	time2 = get_time2(argument, tv);
	if ((time2 - time) >= argument->properties.time_to_die * 1000)
	{
		sem_post(argument->taking);
		return ;
	}
	printf("%lld %d is died \n", time2
		/ 1000, philosophers->number + 1);
	usleep(argument->properties.time_to_die * 10000);
	sem_post(argument->taking);
}

void	*dead_func(void *x)
{
	t_args				*argument;
	struct timeval		tv;
	t_def_properties	properties;
	t_philo				*philosophers;
	long long			time;

	argument = (t_args *) x;
	properties = argument->properties;
	philosophers = argument->philosophers;
	while (!philosophers->have_eaten)
	{
		usleep(1000);
		gettimeofday(&tv, NULL);
		time = (get_time2(argument, tv) / 1000);
		if (!philosophers->have_eaten && time
			- philosophers->last_time >= properties.time_to_die)
		{
			philosophers->is_dead = 1;
			dead_philo(argument, tv);
			return (0);
		}
	}
	return (0);
}
