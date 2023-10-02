/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:24:39 by fracerba          #+#    #+#             */
/*   Updated: 2023/03/23 15:24:42 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	loop_count(t_main *main, int *i)
{
	(*i)++;
	if (*i == main->num_philo)
		*i = 0;
}

void	*loop(void *args)
{
	t_main	*main;
	int		i;

	main = (t_main *)args;
	i = 0;
	if (main->num_each_must_eat > 0)
	{
		while (main->num_each_must_eat > ft_check_eaten(main, i)
			&& !ft_check_dead(main))
		{
			if (philo_dead(main, i))
				return (NULL);
			loop_count(main, &i);
		}
	}
	else
	{
		while (!ft_check_dead(main))
		{
			if (philo_dead(main, i))
				return (NULL);
			loop_count(main, &i);
		}
	}
	return (NULL);
}

int	philo_routine(t_main *main, int i)
{
	if (!philo_eat(main, i))
		return (0);
	if (main->num_each_must_eat != ft_check_eaten(main, i))
	{
		if (!philo_sleep(main, i))
			return (0);
		if (!philo_think(main, i))
			return (0);
	}
	return (1);
}

void	*life(void *args)
{
	t_main	*main;
	int		i;

	main = (t_main *)args;
	pthread_mutex_lock(&main->n_thr);
	i = main->n_threads;
	pthread_mutex_unlock(&main->n_thr);
	if (main->num_each_must_eat > 0)
	{
		while (main->num_each_must_eat > main->philo[i].t_eaten
			&& !ft_check_dead(main))
		{
			if (!philo_routine(main, i))
				return (NULL);
		}
	}
	else
	{
		while (!ft_check_dead(main))
		{
			if (!philo_routine(main, i))
				return (NULL);
		}
	}
	return (NULL);
}
