/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:46:05 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/16 22:01:27 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	int nb;
	int is_dead;
	int nb_must_eat;
	unsigned long time_to_eat;
	unsigned long time_to_die;
	unsigned long time_to_sleep;
	unsigned long last_meal;
	pthread_mutex_t *fork;
} t_philo;

typedef struct s_var
{
	int nb_of_philo;
	t_philo *philosophers;
	pthread_t *thread_id;
	pthread_mutex_t *forks;
	int nb_must_eat;
	unsigned long time_to_eat;
	unsigned long time_to_die;
	unsigned long time_to_sleep;
} t_var;

int	fill_struct(t_var *var, int argc, char **argv);
int init_mutex(t_var *var);
void init_philo(t_var *var);
void detach_thread(t_var *var, int i);
void join_thread(t_var *var);

#endif
