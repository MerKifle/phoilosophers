/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:42:15 by marvin            #+#    #+#             */
/*   Updated: 2023/05/13 10:54:38 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# define TRUE 1
# define FALSE 0

// typedef struct s_fork
// {
// 	int	left;
// 	int	right;
// }		t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	int				count_eating_times;
	int				*l_fork;
	int				*r_fork;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	struct s_info	*info;
	long long		last_eat_time;
}		t_philo;

typedef struct s_info
{
	long long		start_time;
	int				dead;
	int				n_thread;
	int				philo_num;
	int				times_must_eat;
	long long		time_to_eat;
	long long		time_to_die;
	long long		time_to_sleep;
	pthread_mutex_t	*fork_locker;
	pthread_mutex_t	print;
	pthread_mutex_t	endgame;
	pthread_mutex_t	clear;
	pthread_mutex_t	last_eat_locker;
	int				*forks;
	t_philo			*philo;
}		t_info;

// utils.c
void		display_error_message(int i, int arg);
void		validate_args(char **argv, int argc);
long		ft_atoi(char *str);

//routine
void		*routine(void *philo);
void		display_message(t_info *info, int i, char *str);

//thread_handler
int			create_thread(t_info *info);

//fork_handler
// int			create_fork(t_info *info);
int			create_fork(t_info *info, int num);

//time_handler
time_t	get_time(void);
int			is_dead(t_info *info);
int			waiting_time(t_info *info, time_t start, time_t time);

//checker 
int		checker(t_info *info);
int			someone_died(t_info *info);

// philo
void	clear_all(t_info *info);
#endif
