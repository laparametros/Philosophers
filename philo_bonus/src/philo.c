/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkuyucu <hkuyucu@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:39:47 by muhaaydi          #+#    #+#             */
/*   Updated: 2023/10/07 09:19:47 by hkuyucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	print_state(const char *state, t_args *arguments)
{
	long long	time;

	time = 0;
	sem_wait(arguments->taking);
	if (!arguments->philosophers->is_dead)
	{
		time = get_time(arguments);
		printf(state, time / 1000, arguments->philosophers->number + 1);
		sem_post(arguments->taking);
		return (1);
	}
	sem_post(arguments->taking);
	return (0);
}

int	philo_eaten(t_args *args, int i, int number_eating)
{
	if (i == number_eating)
	{
		args->philosophers->have_eaten = 1;
		return (0);
	}
	return (1);
}

void	*philosophy(void *arg)
{
	t_args	*args;
	int		i;
	int		number_eating;

	args = (t_args *) arg;
	if (args->properties.number_of_philo == 1)
		return (0);
	number_eating = args->properties.number_of_eating;
	i = 0;
	while ((i < number_eating || number_eating == 0)
		&& !args->philosophers->is_dead)
	{
		set_fork(args);
		if (!eat_philo(args))
			return (0);
		i++;
		left_forks(args);
		if (!sleep_philo(args))
			return (0);
		if (!philo_eaten(args, i, number_eating))
			return (0);
		think_philo(args);
	}
	return (0);
}

void	allocate_properties(t_args *argument)
{
	int	i;

	i = 0;
	argument->pid_list = (pid_t **) malloc(sizeof(pid_t *)
			* argument->properties.number_of_philo);
	if (!argument->pid_list)
		free_error_state(argument);
	argument->philosophers = (t_philo *) malloc(sizeof(t_philo));
	if (!argument->philosophers)
		free_error_state(argument);
	argument->dead_control = (pthread_t *) malloc(sizeof(pthread_t));
	if (!argument->dead_control)
		free_error_state(argument);
	while (i < argument->properties.number_of_philo)
	{
		argument->pid_list[i] = (pid_t *) malloc(sizeof(pid_t));
		if (!argument->pid_list[i])
			free_error_state(argument);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_args				*argument;
	sem_t				**forks;
	t_def_properties	properties;

	if (argc < 5 || argc > 6)
		exit(1);
	argument = (t_args *) malloc(sizeof(t_args));
	if (!argument)
	{
		printf("Error\n");
		exit (0);
	}
	properties = properties_init(argv, argc);
	argument->properties = properties;
	allocate_properties(argument);
	unlink_sems(argument);
	argument->taking = sem_open("taking", O_EXCL | O_CREAT, 0666, 1);
	forks = forks_init(argument);
	philo_properties(argument, forks);
	children_init(argument);
	destroy_properties(argument);
	exit(1);
}
