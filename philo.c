/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:36:01 by mkiflema          #+#    #+#             */
/*   Updated: 2023/05/13 10:52:07 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
	{
		// if (info->forks[i] == 1)
		// 	pthread_mutex_unlock(&info->fork_locker[i]); 
		pthread_mutex_destroy(&info->fork_locker[i]);
	}
	pthread_mutex_destroy(&info->last_eat_locker);
	pthread_mutex_destroy(&info->endgame);
	free(info->forks);
	free(info->fork_locker);
	pthread_mutex_destroy(&info->print);
}

void	clear_all(t_info *info)
{
	destroy_mutex(info);
	pthread_mutex_destroy(&info->clear);
	free(info->philo);
	free(info);
	return ;
}

void	feed_philo(t_info *info, char **argv, int philo_num, int argc)
{

	int			i;
	long long	current_time;

	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->times_must_eat = 0;
	if (argc == 6)
		info->times_must_eat = ft_atoi(argv[5]);
	info->dead = 0;
	i = -1;
	current_time = get_time();
	while (++i < info->philo_num)
	{
		info->philo[i].id = i + 1;
		info->philo[i].l_fork = &(info->forks[i]);
		info->philo[i].r_fork = &(info->forks[(i + 1) % info->philo_num]);
		info->philo[i].left = &(info->fork_locker[i]);;
		info->philo[i].right = &(info->fork_locker[(i + 1) % info->philo_num]);;
		info->philo[i].last_eat_time = current_time;
		info->philo[i].info = info;
		info->philo[i].count_eating_times = 0;
	}
}

int	create_philos(t_info *info, char **argv, int philo_num, int argc)
{
	int	i;

	info->philo_num = philo_num;
	info->philo = malloc(sizeof(t_philo) * (philo_num + 1));
	if (!info->philo)
		return (FALSE);
	feed_philo(info, argv, philo_num, argc);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	int			num;
	t_info		*info;

	if (argc == 5 || argc == 6)
	{
		validate_args(argv + 1, argc);
		num = ft_atoi(argv[1]);
		info = malloc(sizeof(t_info));
		if (!create_fork(info, num))
		{
			free(info->philo);
			destroy_mutex(info);
			pthread_mutex_destroy(&info->clear);
			return (1);
		}
		if (!create_philos(info, argv, num, argc))
		{
			free(info->philo);
			return (1);
		}
		// if (!create_fork(info))
		// {
		// 	free(info->philo);
		// 	destroy_mutex(info);
		// 	pthread_mutex_destroy(&info->clear);
		// 	return (1);
		// }
		
		if (create_thread(info) == 0)
		{
			clear_all(info);
			return (1);
		}
		clear_all(info);
	}
}
