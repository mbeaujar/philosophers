/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 19:40:59 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/19 17:16:04 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void sleep_time(unsigned long len)
{
	unsigned long time;

	time = get_time();
	while (get_time() - time < len)
		usleep(100);
}

void print_msg(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->msg);
	if (*philo->is_dead == 0)
		printf("%lu\t#%d %s\n", get_time() - *philo->time_start, philo->nb + 1, str);
	pthread_mutex_unlock(philo->msg);
}