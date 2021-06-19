/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:45:17 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/19 19:03:50 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_mutex(t_var *var, int i)
{
	while (i-- > 0)
		pthread_mutex_destroy(&var->forks[i]);
	return (1);
}

int	init_mutex(t_var *var)
{
	int	i;

	i = -1;
	while (++i < var->nb_of_philo)
	{
		if (pthread_mutex_init(&var->forks[i], NULL) != 0)
		{
			free(var->philosophers);
			free(var->forks);
			return (free_mutex(var, i));
		}
	}
	var->id = malloc(sizeof(pthread_t) * var->nb_of_philo);
	if (!var->id)
	{
		free(var->philosophers);
		free(var->forks);
		return (free_mutex(var, var->nb_of_philo));
	}
	pthread_mutex_init(&var->msg, NULL);
	return (0);
}

int	create_thread(t_var *var)
{
	int	i;

	i = -1;
	var->time_start = get_time();
	while (++i < var->nb_of_philo)
	{
		if (pthread_create(&var->id[i], NULL, routine, &var->philosophers[i]))
			return (1);
		usleep(70);
	}
	return (0);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	sleep_time(unsigned long len)
{
	unsigned long	time;

	time = get_time();
	while (get_time() - time < len)
		usleep(100);
}
