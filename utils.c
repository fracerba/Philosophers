/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:25:51 by fracerba          #+#    #+#             */
/*   Updated: 2023/03/23 15:25:53 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		nb = nb * 10;
		nb = nb + nptr[i] - 48;
		i++;
	}
	if (nptr[i])
		return (-1);
	return (nb);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;	

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < (n - 1))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_philo(t_main *main)
{
	free(main->philo);
	free(main->forks);
	return ;
}
