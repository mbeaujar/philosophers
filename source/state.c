/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:14:20 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/19 17:19:29 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->nb]);
	print_msg(philo, "has taken a fork");
	if (philo->nb + 1 == philo->max_nb)
		pthread_mutex_lock(&philo->forks[0]);
	else
		pthread_mutex_lock(&philo->forks[philo->nb + 1]);
	print_msg(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meals);
	philo->last_meal = get_time();
	print_msg(philo, "is eating");
	sleep_time(philo->time_to_eat);
	pthread_mutex_unlock(&philo->meals);
	if (philo->nb + 1 == philo->max_nb)
		pthread_mutex_unlock(&philo->forks[0]);
	else
		pthread_mutex_unlock(&philo->forks[philo->nb + 1]);
	pthread_mutex_unlock(&philo->forks[philo->nb]);
	philo->nb_eaten++;
}