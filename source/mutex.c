/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:45:17 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/18 23:00:35 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void free_mutex(t_var *var, int i)
{
	while (i-- > 0)
		pthread_mutex_destroy(&var->forks[i]);
}

void destroy_mutex(t_var *var)
{
	int i;

	i = 0;
	while (i < var->nb_of_philo)
	{
		pthread_mutex_destroy(&var->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&var->msg);
}

int init_mutex(t_var *var)
{
	int i;

	i = 0;
	while (i < var->nb_of_philo)
	{
		if (pthread_mutex_init(&var->forks[i], NULL) != 0)
		{
			free_mutex(var, i);
			return (1);
		}
		i++;
	}
	pthread_mutex_init(&var->msg, NULL);
	var->thread_id = malloc(sizeof(pthread_t) * var->nb_of_philo);
	if (!var->thread_id)
	{
		pthread_mutex_destroy(&var->msg);
		free_mutex(var, var->nb_of_philo);
		return (1);
	}
	return (0);
}
