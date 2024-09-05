/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:40:49 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/10/05 15:06:18 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	get_time(t_args *arguments)
{
	long long			time;
	t_def_properties	properties;

	properties = arguments->properties;
	if (!arguments->philosophers->is_dead)
	{
		if (arguments->philosophers->is_dead)
			return (0);
		gettimeofday(&(properties.current_time), NULL);
		time = (properties.current_time.tv_sec - properties.tv.tv_sec)
			* 1000000 + properties.current_time.tv_usec - properties.tv.tv_usec;
		return (time);
	}
	return (0);
}

long long	get_time2(t_args *arguments, struct timeval tv2)
{
	long long			time;
	t_def_properties	properties;

	properties = arguments->properties;
	gettimeofday(&tv2, NULL);
	time = (tv2.tv_sec - properties.tv.tv_sec)
		* 1000000 + tv2.tv_usec - properties.tv.tv_usec;
	return (time);
}
