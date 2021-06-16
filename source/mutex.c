/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:45:17 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/16 22:02:54 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void free_mutex(t_var *var, int i)
{
	while (i-- > 0)
		pthread_mutex_destroy(&var->forks[i]);
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
	var->thread_id = malloc(sizeof(pthread_t) * var->nb_of_philo);
	if (!var->thread_id)
		return (1);
	return (0);
}



void init_philo(t_var *var)
{
	int i;

	i = 0;
	while (i < var->nb_of_philo)
	{
		var->philosophers[i].fork = var->forks;
		var->philosophers[i].is_dead = 0;
		var->philosophers[i].last_meal = -1;
		var->philosophers[i].nb = i;
		var->philosophers[i].nb_must_eat = var->nb_must_eat;
		var->philosophers[i].time_to_die = var->time_to_die;
		var->philosophers[i].time_to_eat = var->time_to_eat;
		var->philosophers[i].time_to_eat = var->time_to_sleep;
		i++;
	}
}