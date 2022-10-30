/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:37:22 by amounach          #+#    #+#             */
/*   Updated: 2022/10/30 06:35:01 by amounach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long long ms)
{
	long long	now;

	now = get_time();
	while ((get_time() - now) < ms)
		usleep(20);
}

int	main(int ac, char **av)
{
	if ((ac == 5 || ac == 6) && (parse_input(ac, av)))
		allocate(av);
	else
		printf("Error: Arguments\n");
}
