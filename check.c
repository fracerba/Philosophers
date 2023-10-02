/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:17:50 by fracerba          #+#    #+#             */
/*   Updated: 2023/03/30 16:17:53 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_check_dead(t_main *main)
{
	int	i;

	pthread_mutex_lock(&main->m_dead);
	i = main->dead;
	pthread_mutex_unlock(&main->m_dead);
	return (i);
}

int	ft_check_to_die(t_main *main, int j)
{
	int	i;

	pthread_mutex_lock(&main->philo[j].to_die);
	i = main->philo[j].t_to_die;
	pthread_mutex_unlock(&main->philo[j].to_die);
	return (i);
}

int	ft_check_eaten(t_main *main, int j)
{
	int	i;

	pthread_mutex_lock(&main->philo[j].eaten);
	i = main->philo[j].t_eaten;
	pthread_mutex_unlock(&main->philo[j].eaten);
	return (i);
}
