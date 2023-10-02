/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:24:27 by fracerba          #+#    #+#             */
/*   Updated: 2023/03/23 15:24:30 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init_main(int argc, char **argv, t_main *main)
{
	main->num_philo = ft_atoi(argv[1]);
	main->time_to_die = ft_atoi(argv[2]);
	main->time_to_eat = ft_atoi(argv[3]);
	main->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		main->num_each_must_eat = ft_atoi(argv[5]);
	else
		main->num_each_must_eat = -1;
	main->dead = 0;
}

void	init_one_philo(t_main *main, int i, int j)
{
	main->philo[i - 1].num = i;
	main->philo[i - 1].t_eaten = 0;
	main->philo[i - 1].t_to_die = 0;
	main->philo[i - 1].left_f = i;
	main->philo[i - 1].right_f = j;
}

int	ft_init_philo(t_main *main)
{
	int	i;

	main->philo = malloc(sizeof(t_philo) * (main->num_philo));
	if (main->philo == NULL)
		return (0);
	i = 1;
	while (i < main->num_philo)
	{
		init_one_philo(main, i, i + 1);
		i++;
	}
	init_one_philo(main, i, 1);
	return (1);
}

int	ft_init_forks(t_main *main)
{
	int	i;

	main->forks = malloc(sizeof(pthread_mutex_t) * (main->num_philo));
	if (main->forks == NULL)
		return (0);
	i = 0;
	while (i < main->num_philo)
	{
		if (pthread_mutex_init(&main->forks[i], NULL))
			return (0);
		i++;
	}
	return (1);
}
