/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:34:58 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/10/05 15:05:57 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eat_philo(t_args *args)
{
	if (!print_state("%lld %d has taken a fork\n", args))
	{
		left_forks(args);
		return (0);
	}
	if (!print_state("%lld %d has taken a fork\n", args))
	{
		left_forks(args);
		return (0);
	}
	args->philosophers->last_time = get_time(args) / 1000;
	if (!print_state("%lld %d is eating\n", args))
	{
		left_forks(args);
		return (0);
	}
	ft_sleep(args->properties.time_to_eat * 1000, *args);
	return (1);
}
