/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:57:26 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/16 22:03:13 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void detach_thread(t_var *var, int i)
{
	while (i-- > 0)
		pthread_detach(var->thread_id[i]);
}

void join_thread(t_var *var)
{
	int i;

	i = 0;
	while (i < var->nb_of_philo)
	{
		pthread_join(var->thread_id[i], NULL);
		pthread_mutex_destroy(&var->forks[i]);
		i++;
	}
}