/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:25:21 by fracerba          #+#    #+#             */
/*   Updated: 2023/03/23 15:25:24 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_mutex(t_main *main)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&main->print, NULL))
		return (0);
	if (pthread_mutex_init(&main->m_dead, NULL))
		return (0);
	if (pthread_mutex_init(&main->n_thr, NULL))
		return (0);
	while (i < main->num_philo)
	{
		if (pthread_mutex_init(&main->philo[i].to_die, NULL))
			return (0);
		if (pthread_mutex_init(&main->philo[i].eaten, NULL))
			return (0);
		i++;
	}
	return (0);
}

int	ft_init_threads(t_main *main)
{
	int	i;

	i = 0;
	main->time = gettime();
	main->dead = 0;
	if (ft_init_mutex(main))
		return (0);
	while (i < main->num_philo)
	{
		pthread_mutex_lock(&main->n_thr);
		main->n_threads = i;
		pthread_mutex_unlock(&main->n_thr);
		if (pthread_create(&main->philo[i].thread, NULL, &life, (void *)main))
			return (0);
		i++;
		usleep (1000);
	}
	if (pthread_create(&main->waiter, NULL, &loop, (void *)main))
		return (0);
	usleep (1000);
	if (!ft_link_threads(main))
		return (0);
	return (1);
}

int	ft_link_threads(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->num_philo)
	{
		if (pthread_join(main->philo[i].thread, NULL))
			return (0);
		i++;
	}
	if (pthread_join(main->waiter, NULL))
		return (0);
	return (1);
}

int	ft_destroy_threads(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->num_philo)
	{
		if (pthread_mutex_destroy(&main->forks[i]))
			return (0);
		if (pthread_mutex_destroy(&main->philo[i].to_die))
			return (0);
		if (pthread_mutex_destroy(&main->philo[i].eaten))
			return (0);
		i++;
	}
	if (pthread_mutex_destroy(&main->print))
		return (0);
	if (pthread_mutex_destroy(&main->m_dead))
		return (0);
	if (pthread_mutex_destroy(&main->n_thr))
		return (0);
	return (1);
}

int	philo_print(t_main *main, int num, char *action)
{
	long long	time;

	time = time_diff(main->time);
	if (ft_check_dead(main))
		return (0);
	pthread_mutex_lock(&main->print);
	if (ft_check_dead(main))
	{
		pthread_mutex_unlock(&main->print);
		return (0);
	}
	else
		printf("%lli %i %s\n", time, num, action);
	pthread_mutex_unlock(&main->print);
	return (1);
}
