/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:28:35 by amounach          #+#    #+#             */
/*   Updated: 2022/10/30 03:12:32 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    set_forks(t_pthread *philo, int x)
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

void   eating(t_pthread *philo)
{
    print(philo, "is eating", 1);
    usleep(philo->data->t_eat * 1e3);
    philo->time = get_time();
    philo->n_eat -= 1;
}

void *routine(void *arg)
{
    t_pthread   *philo;
    int         check;
    
    check = 0;
    philo = (t_pthread*)arg;
    while(check == 0)
    {
        set_forks(philo, 0);
        eating(philo);
        set_forks(philo, 1);
        usleep(philo->data->t_sleep * 1e3);
        print(philo, "is sleeping", 1);
        print(philo, "is thinking", 1);
        if (philo->data->philos->n_eat == 0)
            check = 1;
    }
    return (NULL);
}

void    create_thread(t_pthread *philo)
{
    int i;

    i = -1;
    while (++i < philo->data->n_philo)
        pthread_create(&philo[i].thread_id, NULL, &routine, &philo[i]);
    i = 0;
    while (++i < philo->data->n_philo)
        pthread_join(philo[i].thread_id, NULL);
}

void check_death(t_pthread *philo)
{
    if (get_time() - philo->time > philo->data->t_die)
    {
        print(philo, "is died", 1);
    }  
}