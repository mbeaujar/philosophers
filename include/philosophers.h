/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:46:05 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/19 15:04:32 by mbeaujar         ###   ########.fr       */
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
	int max_nb;
	int *is_dead;
	int nb_must_eat;
	int nb_eaten;
	unsigned long *time_start;
	unsigned long time_to_eat;
	unsigned long time_to_die;
	unsigned long time_to_sleep;
	unsigned long last_meal;
	pthread_mutex_t *forks;
	pthread_mutex_t *msg;
} t_philo;

typedef struct s_var
{
	int is_dead;
	int nb_of_philo;
	t_philo *philosophers;
	pthread_t *thread_id;
	pthread_mutex_t *forks;
	pthread_mutex_t msg;
	int nb_must_eat;
	unsigned long time_start;
	unsigned long time_to_eat;
	unsigned long time_to_die;
	unsigned long time_to_sleep;
} t_var;

int	fill_struct(t_var *var, int argc, char **argv);
int init_mutex(t_var *var);
void init_philo(t_var *var);
int detach_thread(t_var *var);
void join_thread(t_var *var);
void eat(t_philo *philo);
unsigned long get_time(void);
void sleep_time(unsigned long len);
int create_thread(t_var *var);
void *routine(void *vargp);
void print_msg(t_philo *philo, char *str);
void destroy_mutex(t_var *var);

#endif
