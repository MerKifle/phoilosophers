/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:09:33 by marvin            #+#    #+#             */
/*   Updated: 2023/06/03 17:38:22 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	result;
	int		count;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] && (str[i] >= 9 && str[i] <= 13 || str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	count = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		count++;
		if (count > 10)
			return (0);
		result = result * 10 + (str[i++] - '0');
	}
	while (str[i] && !(str[i] >= '0' && str[i] <= '9'))
		return (0);
	return (result * sign);
}

void	display_error_message(int i, int arg)
{
	if (i == -1)
		printf("Arg number %d is null", arg);
	else if (i == 0)
		printf("Arg number %d should be greater than 0", arg);
	else if (i == 1)
		printf("Arg number %d is not numberic", arg);
	exit(1);
}

static int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9' || str[i] == '+' || str[i] == '-'))
			return (0);
		i++;
	}
	return (1);
}

void	validate_args(char **argv, int argc)
{
	int	i;

	i = 0;
	if (!argv[i])
		display_error_message(-1, 1);
	while (argv[i])
	{
		if (!argv[i] || !argv[i][0])
			display_error_message(-1, i + 1);
		if (!is_num(argv[i]))
			display_error_message(1, i + 1);
		if (argv[i][0] == '0' && argv[i][1] == '\0')
			display_error_message(0, 1);
		if (ft_atoi(argv[i]) <= 0)
			display_error_message(0, i + 1);
		i++;
	}
}
