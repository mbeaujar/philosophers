/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:45:48 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/20 20:31:32 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
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
	philo->nb_eat++;
}

void	*monitor(void *vargp)
{
	t_philo	*philo;

	philo = (t_philo *)vargp;
	while (*philo->is_dead == 0)
	{
		pthread_mutex_lock(&philo->meals);
		if (get_time() - philo->last_meal >= philo->time_to_die)
		{
			print_msg(philo, "died");
			*philo->is_dead = 1;
			if (philo->max_nb == 1)
				pthread_mutex_unlock(&philo->forks[0]);
			pthread_mutex_unlock(&philo->meals);
			break ;
		}
		else if (philo->must_eat != -1 && philo->nb_eat >= philo->must_eat)
		{
			pthread_mutex_unlock(&philo->meals);
			break ;
		}
		pthread_mutex_unlock(&philo->meals);
		usleep(500);
	}
	return (NULL);
}

void	*routine(void *vargp)
{
	t_philo		*philo;
	pthread_t	id;

	philo = (t_philo *)vargp;
	philo->last_meal = get_time();
	pthread_mutex_init(&philo->meals, NULL);
	pthread_create(&id, NULL, monitor, philo);
	while (*philo->is_dead == 0)
	{
		eat(philo);
		if (*philo->is_dead == 1 || (philo->must_eat != -1
				&& philo->nb_eat >= philo->must_eat))
			break ;
		print_msg(philo, "is sleeping");
		sleep_time(philo->time_to_sleep);
		if (*philo->is_dead == 1)
			break ;
		print_msg(philo, "is thinking");
	}
	pthread_mutex_destroy(&philo->meals);
	pthread_join(id, NULL);
	return (NULL);
}

void	init_philo(t_var *var)
{
	int	i;

	i = -1;
	while (++i < var->nb_of_philo)
	{
		var->philosophers[i].forks = var->forks;
		var->philosophers[i].is_dead = &var->is_dead;
		var->philosophers[i].last_meal = -1;
		var->philosophers[i].nb = i;
		var->philosophers[i].nb_eat = 0;
		var->philosophers[i].max_nb = var->nb_of_philo;
		var->philosophers[i].must_eat = var->must_eat;
		var->philosophers[i].time_to_die = var->time_to_die;
		var->philosophers[i].time_to_eat = var->time_to_eat;
		var->philosophers[i].time_to_sleep = var->time_to_sleep;
		var->philosophers[i].time_start = &var->time_start;
		var->philosophers[i].msg = &var->msg;
	}
}

int	main(int argc, char **argv)
{
	t_var	var;
	int		i;

	i = -1;
	if (argc < 5 || argc > 6)
		return (printf("Wrong number of arguments.\n") - 26);
	if (fill_struct(&var, argc, argv) || init_mutex(&var))
		return (1);
	init_philo(&var);
	create_thread(&var);
	while (++i < var.nb_of_philo)
		pthread_join(var.id[i], NULL);
	pthread_mutex_destroy(&var.msg);
	free(var.philosophers);
	free(var.forks);
	free(var.id);
	if (var.must_eat != -1 && var.is_dead == 0)
		printf("%lu\t%s\n", get_time() - var.time_start,
			"Everyone has eaten enough !");
	return (0);
}
