/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:46:05 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/20 19:22:33 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				nb;
	int				max_nb;
	int				*is_dead;
	int				must_eat;
	int				nb_eat;
	unsigned long	*time_start;
	unsigned long	time_to_eat;
	unsigned long	time_to_die;
	unsigned long	time_to_sleep;
	unsigned long	last_meal;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*msg;
	pthread_mutex_t	meals;
}		t_philo;

typedef struct s_var
{
	int				is_dead;
	int				nb_of_philo;
	int				must_eat;
	t_philo			*philosophers;
	pthread_t		*id;
	unsigned long	time_start;
	unsigned long	time_to_eat;
	unsigned long	time_to_die;
	unsigned long	time_to_sleep;
	pthread_mutex_t	msg;
	pthread_mutex_t	*forks;
}		t_var;

unsigned long	get_time(void);
void			sleep_time(unsigned long len);
void			*routine(void *vargp);
void			print_msg(t_philo *philo, char *str);
int				fill_struct(t_var *var, int argc, char **argv);
int				create_thread(t_var *var);
int				init_mutex(t_var *var);
void			print_msg_death(t_philo *philo);

#endif
