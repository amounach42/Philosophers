/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:37:22 by amounach          #+#    #+#             */
/*   Updated: 2022/10/30 02:35:23 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_atoi(char *str)
{
    int i;
    int res;

    i = 0;
    res = 0;

    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            return(0);
        i++;
    }
    while (str[i])
    {
            if (!(str[i] >= '0' && str[i] <= '9'))
                return (0);
            res = (res * 10) + (str[i++] - 48);
    }
    return (res);
}

int parse_input(int ac, char **av)
{
    int i;
    
    i = 0;
    while (++i < ac)
    {
        if (ft_atoi(av[i]) == 0)
            return (0);
    }
    return (1);
}

