# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 20:32:15 by mkiflema          #+#    #+#              #
#    Updated: 2023/06/10 17:18:31 by mkiflema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

M_SRCS	= philo.c fork_handler.c  utils.c thread_handler.c  routine.c time_handler.c checker.c
M_OBJCS	= $(M_SRCS:.c=.o)

Cdead	=  -Wextra -Werror -Wall -g -pthread
CC		= cc
RM		= rm -f


all: $(NAME)

$(NAME): $(M_OBJCS)
	$(CC) $(Cdead)	$(M_OBJCS) -o $(NAME)

clean: 
	$(RM) $(M_OBJCS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norminette:
	norminette *.c 


