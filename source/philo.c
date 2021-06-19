/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:45:48 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/19 14:35:15 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine(void *vargp)
{
	t_philo *philo;

	philo = (t_philo*)vargp;
	while (philo->is_dead == 0)
	{
		eat(philo);
		if (philo->is_dead == 1 || (philo->nb_must_eat != -1 && philo->nb_eaten >= philo->nb_must_eat))
			break ;
		print_msg(philo, "is sleeping");
		sleep_time(philo->time_to_sleep);
		if (philo->is_dead == 1)
			break ;
		print_msg(philo, "is thinking");
	}
	return (NULL);
}

void init_philo(t_var *var)
{
	int i;

	i = 0;
	while (i < var->nb_of_philo)
	{
		var->philosophers[i].forks = var->forks;
		var->philosophers[i].is_dead = 0;
		var->philosophers[i].last_meal = -1;
		var->philosophers[i].nb = i;
		var->philosophers[i].nb_eaten = 0;
		var->philosophers[i].max_nb = var->nb_of_philo;
		var->philosophers[i].nb_must_eat = var->nb_must_eat;
		var->philosophers[i].time_to_die = var->time_to_die;
		var->philosophers[i].time_to_eat = var->time_to_eat;
		var->philosophers[i].time_to_sleep = var->time_to_sleep;
		var->philosophers[i].time_start = &var->time_start;
		var->philosophers[i].msg = &var->msg;
		i++;
	}
}

int main(int argc, char **argv)
{
	t_var var;
	
	if (argc < 5 || argc > 6)
		return (printf("Wrong number of arguments.\n"));
	if (fill_struct(&var, argc, argv))
		return (1);
	if (init_mutex(&var))
		return (1);
	init_philo(&var);
	if (create_thread(&var))
		return (1);
	join_thread(&var);
	destroy_mutex(&var);
	free(var.philosophers);
	free(var.forks);
	free(var.thread_id);
	return (0);
}