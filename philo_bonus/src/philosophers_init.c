/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:40:24 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/10/07 08:42:21 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <sys/wait.h>

sem_t	**forks_init(t_args *arg)
{
	int		i;
	sem_t	**forks;
	char	*str;

	i = 0;
	forks = (sem_t **) malloc(sizeof(sem_t *)
			* arg->properties.number_of_philo);
	while (i < arg->properties.number_of_philo)
	{
		str = ft_sprintf(i);
		forks[i] = sem_open(str, O_EXCL | O_CREAT, 0666, 1);
		free(str);
		i++;
	}
	return (forks);
}

void	philo_properties(t_args *argument, sem_t **forks)
{
	argument->forks = forks;
	argument->philosophers->last_time = 0;
	argument->philosophers->have_eaten = 0;
	argument->philosophers->is_dead = 0;
}

t_def_properties	properties_init(char **argv, int argc)
{
	t_def_properties	default_pro;
	struct timeval		current_time;
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	gettimeofday(&current_time, NULL);
	default_pro.current_time = current_time;
	default_pro.tv = tv;
	if (argc == 5)
		default_pro.number_of_eating = 0;
	else
		default_pro.number_of_eating = ft_atoi(argv[5]);
	default_pro.number_of_philo = ft_atoi(argv[1]);
	default_pro.time_to_die = ft_atoi(argv[2]);
	default_pro.time_to_eat = ft_atoi(argv[3]);
	default_pro.time_to_sleep = ft_atoi(argv[4]);
	if (!control_args(default_pro))
	{
		printf("Error! Invalid argument \n");
		exit(0);
	}
	return (default_pro);
}

void	child_init(t_args *argument)
{
	int	res;

	res = pthread_create(argument->dead_control, NULL,
			dead_func, (void *)argument);
	if (res)
	{
		printf("Error\n");
		destroy_properties(argument);
		exit(0);
	}
	philosophy(argument);
	pthread_join(*argument->dead_control, NULL);
	exit(0);
}

void	children_init(t_args *argument)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < argument->properties.number_of_philo)
	{
		argument->philosophers->number = i;
		pid = fork();
		if (pid == 0)
			child_init(argument);
		if (pid == -1)
		{
			printf("Child process couldn't create \n");
			destroy_properties(argument);
			exit(0);
		}
		*(argument->pid_list[i]) = pid;
		usleep(100);
		i += 2;
		if (i % 2 == 0 && i >= argument->properties.number_of_philo)
			i = 1;
	}
	i = 0;
	while (i < argument->properties.number_of_philo)
		waitpid(*argument->pid_list[i++], NULL, 0);
}
