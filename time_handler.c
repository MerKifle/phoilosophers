/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:27:02 by mkiflema          #+#    #+#             */
/*   Updated: 2023/06/10 19:39:03 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	waiting_time(t_info *info, time_t start, time_t time)
{
	 long long	t_start;;
	 while (get_time() - start < time)
	 {
		if (someone_died(info))
			return (0);
		usleep(200);
	 }
	 return(1);
}
