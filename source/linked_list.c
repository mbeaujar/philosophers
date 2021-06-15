/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:56:13 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/14 18:57:41 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo *newlstphilo(void)
{
	t_philo *new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	return (new);
}
