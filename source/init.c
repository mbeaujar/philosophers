/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:12:36 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/16 22:01:36 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int valid_argument(char *str)
{
	while (*str)
	{
		if (*str < '0' && *str > '9')
			return (1);
		str++;
	}
	return (0);
}

int atoint(char *str)
{
	int nb;

	nb = 0;
	while (*str >= '0' && *str <= '9')
		nb = (nb * 10) + (*str++ - '0');
	return (nb);
}

unsigned long atoul(char *str)
{
	unsigned long nb;

	nb = 0;
	while (*str >= '0' && *str <= '9')
		nb = (nb * 10) + (*str++ - '0');
	return (nb);
}

int	fill_struct(t_var *var, int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc - 1)
	{
		if (valid_argument(argv[i]))
			return (1);
		i++;
	}
	var->nb_of_philo = atoint(argv[1]);
	var->time_to_die = atoul(argv[2]);
	var->time_to_eat = atoul(argv[3]);
	var->time_to_sleep = atoul(argv[4]);
	if (argc == 6)
		var->nb_must_eat = atoint(argv[5]);
	var->philosophers = malloc(sizeof(t_philo) * var->nb_of_philo);
	if (!var->philosophers)
		return (1);
	var->forks = malloc(sizeof(pthread_mutex_t) * var->nb_of_philo);
	if (!var->forks)
	{
		free(var->philosophers);
		return (1);
	}
	return (0);
}