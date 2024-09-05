/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:34:36 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/10/05 15:05:49 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	control_args(t_def_properties properties)
{
	if (properties.number_of_philo < 1)
		return (0);
	if (properties.time_to_die < 0)
		return (0);
	if (properties.time_to_sleep < 0)
		return (0);
	if (properties.time_to_eat < 0)
		return (0);
	if (properties.number_of_eating < 0)
		return (0);
	return (1);
}
