# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fracerba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 10:31:08 by fracerba          #+#    #+#              #
#    Updated: 2023/01/31 10:31:11 by fracerba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Philosophers

SRCS = philosophers.c \
	utils.c \
	initialization.c \
	threads.c \
	actions.c \
	loop.c \
	check.c \

OBJS = ${SRCS:.c=.o}

CC = gcc

RM = rm -f

FLAGS = -Wall -Werror -Wextra -g -pthread

.c.o: 
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	${CC} ${FLAGS} -o ${NAME} ${OBJS}

all: ${NAME}

clean: 
	${RM} ${OBJS}

fclean: clean 
	${RM} ${NAME}

re: fclean all
