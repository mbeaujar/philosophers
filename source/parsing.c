/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:12:36 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/19 19:03:28 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_msg(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->msg);
	if (*philo->is_dead == 0)
		printf("%lu\t%d %s\n",
			get_time() - *philo->time_start, philo->nb + 1, str);
	pthread_mutex_unlock(philo->msg);
}

int	atoint(char *str)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (nb);
}

unsigned long	atoul(char *str)
{
	unsigned long	nb;
	int				i;

	nb = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (nb);
}

int	check_arguments(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("bad arguments\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	fill_struct(t_var *var, int argc, char **argv)
{
	if (check_arguments(argc, argv))
		return (1);
	var->nb_of_philo = atoint(argv[1]);
	var->time_to_die = atoul(argv[2]);
	var->time_to_eat = atoul(argv[3]);
	var->time_to_sleep = atoul(argv[4]);
	var->nb_must_eat = -1;
	var->is_dead = 0;
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
