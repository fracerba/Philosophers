/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:24:14 by fracerba          #+#    #+#             */
/*   Updated: 2023/03/23 15:24:18 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_sleep(t_main *main, int i)
{
	if (!philo_print(main, main->philo[i].num, "is sleeping"))
		return (0);
	usleep (main->time_to_sleep * 1000);
	return (1);
}

int	philo_eat(t_main *main, int i)
{
	if (pthread_mutex_lock(&main->forks[main->philo[i].left_f - 1]))
		return (0);
	if (!philo_print(main, main->philo[i].num, "has taken a fork"))
	{
		pthread_mutex_unlock(&main->forks[main->philo[i].left_f - 1]);
		return (0);
	}
	if (pthread_mutex_lock(&main->forks[main->philo[i].right_f - 1]))
		return (0);
	if (!philo_print(main, main->philo[i].num, "has taken a fork"))
	{
		philo_forks(main, i);
		return (0);
	}
	if (!philo_print(main, main->philo[i].num, "is eating"))
		return (0);
	pthread_mutex_lock(&main->philo[i].to_die);
	main->philo[i].t_to_die = gettime();
	pthread_mutex_unlock(&main->philo[i].to_die);
	usleep (main->time_to_eat * 1000);
	pthread_mutex_lock(&main->philo[i].eaten);
	main->philo[i].t_eaten++;
	pthread_mutex_unlock(&main->philo[i].eaten);
	philo_forks(main, i);
	return (1);
}

int	philo_think(t_main *main, int i)
{
	if (!philo_print(main, main->philo[i].num, "is thinking"))
		return (0);
	return (1);
}

int	philo_dead(t_main *main, int i)
{
	int	time;

	time = time_diff(ft_check_to_die(main, i));
	if (main->time_to_die <= time)
	{
		philo_print(main, main->philo[i].num, "died");
		pthread_mutex_lock(&main->m_dead);
		main->dead = 1;
		pthread_mutex_unlock(&main->m_dead);
		return (1);
	}
	return (0);
}

int	philo_forks(t_main *main, int i)
{
	if (pthread_mutex_unlock(&main->forks[main->philo[i].left_f - 1]))
		return (0);
	if (pthread_mutex_unlock(&main->forks[main->philo[i].right_f - 1]))
		return (0);
	return (1);
}
