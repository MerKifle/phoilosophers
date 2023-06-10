/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:23:33 by mkiflema          #+#    #+#             */
/*   Updated: 2023/06/10 20:19:48 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	display_message(t_info *info, int i, char *str)
{
	pthread_mutex_lock(&info->print);
	printf(" [%lld] Philo %d %s\n", get_time() - info->start_time, i, str);
	pthread_mutex_unlock(&info->print);
}

int	check_fork(t_philo *phil, int code)
{
	int	status;
	
	status = 0;
	if (code == 1)
	{
		pthread_mutex_lock(phil->left);
		if (*phil->l_fork == 1)
		{
			pthread_mutex_unlock(phil->left);
			return (1);
		}
			// status++;
		pthread_mutex_unlock(phil->left);
		return (0);
	}
	if (code == 2)
	{
		pthread_mutex_lock(phil->right);
		if (*phil->r_fork == 1)
		{
			pthread_mutex_unlock(phil->right);
			return (1);
		}
			// status++;
		pthread_mutex_unlock(phil->right);
		return (0);
	}
	// pthread_mutex_lock(phil->left);
	// if (*phil->l_fork == 1)
	// 	status++;
	// pthread_mutex_unlock(phil->left);
	// pthread_mutex_lock(phil->right);
	// if (*phil->r_fork == 1)
	// 	status++;
	// pthread_mutex_unlock(phil->right);
	// return (status);
}

int	fork_wait(t_philo *phil, t_info *info, int code)
{
	while(1)
	{
		if (someone_died(info))
			return (0);
		if (check_fork(phil, code) == 0)
			break;
	}
	return (1);	
}

// int	pick_up_fork( t_philo *phil ,t_info *info)
// {
// 	if (!someone_died(info))
// 	{
// 		if (!check_fork(phil))
// 		{
// 			pthread_mutex_lock(phil->left);
// 			*phil->l_fork = 1;
// 			pthread_mutex_unlock(phil->left);
// 			display_message(info, phil->id,
// 				"has taken a left fork🥄");
// 			pthread_mutex_lock(phil->right);
// 			*phil->r_fork = 1;
// 			pthread_mutex_unlock(phil->right);
// 			display_message(info, phil->id,
// 				"has taken a right fork🥄");
// 			return (1);
// 		}
// 		else
// 			if (!fork_wait(phil, info))
// 				return (0);
// 	}
// 	return (0);
// }

int	pick_up_fork( t_philo *phil ,t_info *info)
{
	if (!someone_died(info))
	{
		if (check_fork(phil, 1))
		{
			fork_wait(phil, info, 1);
			// if (fork_wait(phil, info, 1))
			// 	return (0);
		}
		pthread_mutex_lock(phil->left);
		*phil->l_fork = 1;
		pthread_mutex_unlock(phil->left);
		display_message(info, phil->id,
			"has taken a left fork🥄");
			
		if (!check_fork(phil, 2))
		{
			fork_wait(phil, info, 2);
			// if (fork_wait(phil, info, 2))
			// 	return (0);
		}
		pthread_mutex_lock(phil->right);
		*phil->r_fork = 1;
		pthread_mutex_unlock(phil->right);
		display_message(info, phil->id,
			"has taken a right fork🥄");
	}
	return (1);
}


int drop_forks(t_philo *phil, t_info *info)
{
	pthread_mutex_lock(phil->right);
	*phil->r_fork = 0;
	pthread_mutex_unlock(phil->right);
	display_message(info, phil->id,
		"has released a right fork🥄");
	pthread_mutex_lock(phil->left);
	*phil->l_fork = 0;
	pthread_mutex_unlock(phil->left);
	display_message(info, phil->id,"has released a left fork🥄");
	return(1);
}

int	put_down_fork(t_philo *phil, t_info *info)
{
	int	res;

	if (!someone_died(info))
	{
		if (check_fork(phil, 2) == 1)
		{
			pthread_mutex_lock(phil->right);
			*phil->r_fork = 0;
			pthread_mutex_unlock(phil->right);
			display_message(info, phil->id,
				"has released a right fork🥄");
		}
		if (check_fork(phil, 1) == 1)
		{
			pthread_mutex_lock(phil->left);
			*phil->l_fork = 0;
			pthread_mutex_unlock(phil->left);
			display_message(info, phil->id,
				"has released a left fork🥄");
			return (1);
		}
	}
	return (0);
}


int	ft_eat(t_philo *phil, t_info *info)
{
	if (someone_died(info))
		return(drop_forks(phil, info), 0);
	display_message(info, phil->id, "is eating😋");
	pthread_mutex_lock(&info->last_eat_locker);
	phil->count_eating_times++;
	pthread_mutex_unlock(&info->last_eat_locker);
	phil->last_eat_time = get_time();
	if (!waiting_time(info, get_time(), info->time_to_eat))
		return (0);
	return(1);
}
int	ft_sleep(t_philo *phil, t_info *info)
{
	if (someone_died(info))
		return(0);
	display_message(info, phil->id, "is sleeping😴");
	if (!waiting_time(info, get_time(), info->time_to_sleep))
		return (0);
	return(1);
}

int	ft_think(t_philo *phil, t_info *info)
{
	if (someone_died(info))
		return (0);
	display_message(info, phil->id, "is thinking🤔");
	return (1);
	// usleep(100);
}

int even_philo(t_philo *phil, t_info *info)
{
	if (!ft_think(phil, info))
		return (0);
	usleep (info->time_to_eat);
	return (1);
}

void	*routine(void *philo)
{
	t_info		*inf;
	t_philo		*phil;
	int			i;

	phil = (t_philo *) philo;
	inf = phil->info;
	if (phil->id %2 == 0)
	{
		if (!even_philo(phil, inf))
			return (void *)1;
	}
	while (!someone_died(inf))
	{
		if (!pick_up_fork( phil, inf))
			return (void *)1;
		if (!ft_eat(phil, inf))
			return (void *)1;
		drop_forks(phil, inf);
		if (!ft_sleep(phil, inf))
			return (void *)1;
		if (!ft_think(phil, inf))
			return (void *)1;
	}
	return (NULL);
}
