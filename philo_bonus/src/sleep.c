/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:40:41 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/10/05 15:06:11 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_sleep(long long time, t_args arguments)
{
	if (!arguments.philosophers->is_dead)
	{
		if (arguments.philosophers->is_dead)
			return (0);
		usleep(time);
	}
	return (1);
}

int	sleep_philo(t_args *args)
{
	if (!print_state("%lld %d is sleeping\n", args))
		return (0);
	ft_sleep(args->properties.time_to_sleep * 1000, *args);
	return (1);
}
