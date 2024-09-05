/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:39:28 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/10/05 15:07:20 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>

void	set_fork(t_args *arg)
{
	int		philo_number;
	int		sum_philo;

	philo_number = arg->philosophers->number;
	sum_philo = arg->properties.number_of_philo;
	sem_wait(arg->forks[philo_number]);
	sem_wait(arg->forks[(philo_number + 1) % sum_philo]);
}

void	left_forks(t_args *args)
{
	int		philo_number;
	int		sum_philo;

	philo_number = args->philosophers->number;
	sum_philo = args->properties.number_of_philo;
	sem_post(args->forks[philo_number]);
	sem_post(args->forks[(philo_number + 1) % sum_philo]);
}
