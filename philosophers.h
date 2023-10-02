/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracerba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:25:06 by fracerba          #+#    #+#             */
/*   Updated: 2023/03/23 15:25:09 by fracerba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				num;
	int				t_eaten;
	int				t_to_die;
	int				left_f;
	int				right_f;
	pthread_t		thread;
	pthread_mutex_t	eaten;
	pthread_mutex_t	to_die;
}	t_philo;

typedef struct s_main
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_each_must_eat;
	long long		time;
	int				dead;
	int				n_threads;
	struct s_philo	*philo;
	pthread_t		waiter;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	n_thr;
}	t_main;

int			check_input(int argc, char **argv);
int			one_philo(t_main *main);
long long	gettime(void);
long long	time_diff(long long i);

int			ft_atoi(const char *nptr);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strlen(char *str);
void		free_philo(t_main *main);

int			ft_check_dead(t_main *main);
int			ft_check_eaten(t_main *main, int i);
int			ft_check_to_die(t_main *main, int i);

void		ft_init_main(int argc, char **argv, t_main *main);
void		init_one_philo(t_main *main, int i, int j);
int			ft_init_philo(t_main *main);
int			ft_init_forks(t_main *main);

int			ft_init_mutex(t_main *main);
int			ft_init_threads(t_main *main);
int			ft_link_threads(t_main *main);
int			ft_destroy_threads(t_main *main);
int			philo_print(t_main *main, int num, char *action);

void		loop_count(t_main *main, int *i);
void		*loop(void *args);
int			philo_routine(t_main *main, int i);
void		*life(void *args);

int			philo_sleep(t_main *main, int i);
int			philo_eat(t_main *main, int i);
int			philo_think(t_main *main, int i);
int			philo_dead(t_main *main, int i);
int			philo_forks(t_main *main, int i);

#endif
