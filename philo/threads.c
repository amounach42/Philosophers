/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:28:35 by amounach          #+#    #+#             */
/*   Updated: 2022/10/30 06:35:50 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_forks(t_pthread *philo, int x)
{
	if (x == 0)
	{
		pthread_mutex_lock(&philo->data->forks[(philo->i - 1) \
		% philo->data->n_philo]);
		print(philo, "taken a fork", 1);
		pthread_mutex_lock(&philo->data->forks[(philo->i) \
		% philo->data->n_philo]);
		print(philo, "taken a fork", 1);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[(philo->i - 1) \
		% philo->data->n_philo]);
		pthread_mutex_unlock(&philo->data->forks[(philo->i) \
		% philo->data->n_philo]);
	}
}

void	eating(t_pthread *philo)
{
	print(philo, "is eating", 1);
	ft_usleep(philo->data->t_eat);
	philo->time = get_time();
	philo->n_eat--;
}

void	*routine(void *arg)
{
	t_pthread	*philo;

	philo = (t_pthread *)arg;
	if (philo->i % 2 != 0)
		ft_usleep(philo->data->t_eat);
	while (philo->n_eat && !philo->data->flag_check_death)
	{
		set_forks(philo, 0);
		eating(philo);
		set_forks(philo, 1);
		ft_usleep(philo->data->t_sleep);
		print(philo, "is sleeping", 1);
		print(philo, "is thinking", 1);
	}
	philo->is_finished = 1;
	return (NULL);
}

void	create_thread(t_pthread *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->n_philo)
	{
		pthread_create(&philo[i].thread_id, NULL, &routine, &philo[i]);
	}
	check_death(philo->data);
}

void	check_death(t_philo *philo)
{
	int	i;
	int	n_eat;

	i = 0;
	n_eat = philo[0].n_eat * philo[0].n_philo;
	while (n_eat)
	{
		if (i == philo->n_philo)
			i = 0;
		if (philo->philos[i].is_finished == 1)
		{
			n_eat--;
			continue ;
		}
		if (get_time() - philo->philos[i].time > philo->t_die)
		{
			print(philo->philos, "is died", 0);
			philo->flag_check_death = 1;
			break ;
		}
		i++;
	}
}
