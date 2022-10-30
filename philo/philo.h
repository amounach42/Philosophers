/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 12:15:27 by amounach          #+#    #+#             */
/*   Updated: 2022/10/30 04:13:34 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_thread
{
    pthread_t   thread_id;
    long long   time;
    int         i;
    int         n_eat;
    struct s_philo  *data;
}   t_pthread;

typedef struct s_philo
{
    int             n_philo;
    long long       time;
    int             t_eat;
    int             t_die;
    int             t_sleep;
    int             n_eat;
    int             flag;
    int             flag_check_death;
    pthread_mutex_t mutex;
    t_pthread       *philos;
    pthread_mutex_t *forks;
}   t_philo;

int ft_atoi(char *str);
int allocate(char **av);
int parse_input(int ac, char **av);
void create_thread(t_pthread *philo);
void    print(t_pthread *philo, char *s, int flag);
long long get_time(void);
void initialize(t_philo *philo, char **av);
void check_death(t_philo *philo);

#endif