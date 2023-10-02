/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:24:54 by fracerba          #+#    #+#             */
/*   Updated: 2023/03/23 15:24:57 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_input(int argc, char **argv)
{
	int	num;
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Errore, numero di argomenti errato!\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		num = ft_atoi(argv[i]);
		if (num < 1)
		{
			printf("Errore, uno degli argomenti non e' valido!\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	one_philo(t_main *main)
{
	if (pthread_mutex_init(&main->print, NULL))
		return (0);
	if (pthread_mutex_init(&main->m_dead, NULL))
		return (0);
	main->time = gettime();
	philo_print(main, 1, "has taken a fork");
	usleep(main->time_to_die * 1000);
	philo_print(main, 1, "died");
	free_philo(main);
	return (1);
}

long long	gettime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long i)
{
	if (i > 0)
	{
		i = gettime() - i;
		return (i);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_main	main;

	if (!check_input(argc, argv))
		return (0);
	ft_init_main(argc, argv, &main);
	if (!ft_init_philo(&main))
		return (0);
	if (!ft_init_forks(&main))
		return (0);
	if (main.num_philo == 1)
	{
		one_philo(&main);
		return (0);
	}
	if (!ft_init_threads(&main))
		return (0);
	if (!ft_destroy_threads(&main))
	{
		free_philo(&main);
		return (0);
	}
	free_philo(&main);
	return (0);
}
