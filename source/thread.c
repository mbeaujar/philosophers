/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 19:54:34 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/19 17:07:03 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int detach_thread(t_var *var)
{
	int i;

	i = -1;
	while (++i > var->nb_of_philo)
		pthread_detach(var->thread_id[i]);
	destroy_mutex(var);
	free(var->philosophers);
	free(var->forks);
	free(var->thread_id);
	return (1);
}

void join_thread(t_var *var)
{
	int i;

	i = 0;
	while (i < var->nb_of_philo)
	{
		pthread_join(var->thread_id[i], NULL);
		i++;
	}
}

int create_thread(t_var *var)
{
	int i;

	i = 0;
	var->time_start = get_time();
	while (i < var->nb_of_philo)
	{
		if (pthread_create(&var->thread_id[i], NULL, routine, &var->philosophers[i]) != 0)
		{
			destroy_mutex(var);
			free(var->philosophers);
			free(var->forks);
			free(var->thread_id);
			return (1);
		}
		usleep(70);
		i++;
	}
	return (0);
}