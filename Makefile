# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/27 16:43:56 by jcourtoi          #+#    #+#              #
#    Updated: 2022/07/08 12:38:51 by jcourtoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

BONUS = pipex_bonus

SRCS =	srcs_n/pipex.c srcs_n/free.c srcs_n/checks.c srcs_n/other_checks.c \
	srcs_n/parsing.c srcs_n/process.c \

SRCS_BONUS =	bonus/pipex_bonus.c bonus/free_bonus.c bonus/checks_bonus.c \
		bonus/process_bonus.c bonus/parsing_bonus.c bonus/here_doc.c \
	       	utils_n/gnl/get_next_line.c utils_n/gnl/get_next_line_utils.c \
		bonus/other_check_bonus.c

INC =	pipex.h

INC_BONUS = bonus/pipex_bonus.h

OBJS =	${SRCS:.c=.o}
OBJS_BONUS =	${SRCS_BONUS:.c=.o}

CC =	cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

all: ${NAME}

bonus: ${BONUS}

${NAME}: ${OBJS} ${INC}
	${MAKE} -C ./utils_n/libft
	${MAKE} -C ./utils_n/ft_printf
	${CC} ${CFLAGS} ${OBJS} -L ./utils_n/ft_printf/*.o \
		./utils_n/ft_printf/libftprintf.a \
		./utils_n/libft/libft.a -o ${NAME}

${BONUS} :${OBJS_BONUS} ${INC_BONUS}
	${MAKE} -C ./utils_n/libft
	${MAKE} -C ./utils_n/ft_printf
	${CC} ${CFLAGS} ${OBJS_BONUS} -L ./utils_n/ft_printf/*.o \
		./utils_n/ft_printf/libftprintf.a \
		./utils_n/libft/libft.a -o ${BONUS}

clean:
	${MAKE} -C ./utils_n/libft fclean
	${MAKE} -C ./utils_n/ft_printf fclean
	${RM} ${OBJS} ${OBJS_BONUS}

fclean: clean
	${RM} ${NAME} ${BONUS}

re: fclean all


.PHONY: all clean fclean re
