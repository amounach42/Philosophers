/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 12:15:27 by amounach          #+#    #+#             */
/*   Updated: 2022/10/30 06:36:39 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate(char **av)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (0);
	philo->n_philo = ft_atoi(av[1]);
	philo->philos = malloc(sizeof(t_pthread) * philo->n_philo);
	if (!philo->philos)
		return (0);
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->n_philo);
	if (!philo->forks)
		return (free(philo->philos), 0);
	initialize(philo, av);
	return (1);
}

void	initialize(t_philo *philo, char **av)
{
	int	i;

	philo->n_philo = ft_atoi(av[1]);
	philo->t_die = ft_atoi(av[2]);
	philo->t_eat = ft_atoi(av[3]);
	philo->t_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->n_eat = ft_atoi(av[5]);
	else
		philo->n_eat = -1;
	philo->flag = 0;
	philo->flag_check_death = 0;
	i = -1;
	philo->time = get_time();
	while (++i < philo->n_philo)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		philo->philos[i].i = i + 1;
		philo->philos[i].n_eat = philo->n_eat;
		philo->philos[i].time = philo->time;
		philo->philos[i].data = philo;
		philo->philos[i].is_finished = 0;
	}
	create_thread(philo->philos);
	return ;
}

void	print(t_pthread *philo, const char *s, int flag)
{
	pthread_mutex_lock(&philo->data->mutex);
	if (s)
		printf("%lld ms: Philosopher %d %s\n", get_time() - philo->data->time, \
		philo->i, s);
	if (flag)
		pthread_mutex_unlock(&philo->data->mutex);
}

long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1e3) + (current_time.tv_usec / 1e3));
}

int	ft_free(t_philo *philo)
{
	int	i;

	i = 1;
	while (i++ < philo->n_philo)
		pthread_mutex_destroy(&philo->forks[i]);
	pthread_mutex_destroy(&(philo->mutex));
	free(philo->philos);
	free(philo->forks);
	return (0);
}
