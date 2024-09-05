/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_properties.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:39:36 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/10/07 08:36:32 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <signal.h>

void	unlink_sems(t_args *argument)
{
	int		i;
	char	*str;

	i = 0;
	sem_unlink("taking");
	while (i < argument->properties.number_of_philo)
	{
		str = ft_sprintf(i);
		sem_unlink(str);
		free(str);
		i++;
	}
}

void	destroy_sems(t_args *argument)
{
	int		i;
	char	*str;

	i = 0;
	sem_close(argument->taking);
	sem_unlink("taking");
	while (i < argument->properties.number_of_philo)
		sem_close(argument->forks[i++]);
	i = 0;
	while (i < argument->properties.number_of_philo)
	{
		str = ft_sprintf(i);
		sem_unlink(str);
		free(str);
		i++;
	}
}

void	free_error_state(t_args *argument)
{
	int	i;

	i = 0;
	if (argument)
		free(argument);
	while (i < argument->properties.number_of_philo)
	{
		if (argument->pid_list[i])
			free(argument->pid_list[i]);
		i++;
	}
	if (argument->pid_list)
		free(argument->pid_list);
	if (argument->philosophers)
		free(argument->philosophers);
	if (argument->dead_control)
		free(argument->dead_control);
	printf("Error\n");
	exit (0);
}

void	destroy_properties(t_args *argument)
{
	int		i;

	i = 0;
	destroy_sems(argument);
	while (i < argument->properties.number_of_philo)
	{
		kill(*(argument->pid_list[i]), SIGTERM);
		free(argument->pid_list[i++]);
	}
	free(argument->pid_list);
	free(argument->forks);
	free(argument->philosophers);
	free(argument->dead_control);
	free(argument);
}
