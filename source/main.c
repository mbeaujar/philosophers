/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:45:48 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/16 22:03:59 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine(void *vargp)
{
	t_philo *philo;

	philo = (t_philo*)vargp;
	printf("oui\n");
	return (NULL);
}

int create_thread(t_var *var)
{
	int i;

	i = 0;
	while (i < var->nb_of_philo)
	{
		if (pthread_create(&var->thread_id[i], NULL, routine, &var->philosophers[i]) != 0)
		{
			detach_thread(var, i);
			return (1);
		}
		i++;
	}
	return (0);
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
	init_mutex(&var);
	if (create_thread(&var))
		return (1);
	join_thread(&var);
	return (0);
}