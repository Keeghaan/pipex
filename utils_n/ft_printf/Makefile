# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/17 12:44:01 by jcourtoi          #+#    #+#              #
#    Updated: 2022/06/01 13:51:54 by jcourtoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

HEADERS =  ft_printf.h ft_commontype.h ft_bases_utils.h

SRCS = ft_printf.c ft_base.c ft_commontype.c ft_bases_utils.c

SRCSBONUS = 

OBJ = $(SRCS:.c=.o)

OBJBONUS = $(SRCSBONUS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

AR = ar rcs

all: $(NAME)

compile:
	$(CC) $(CFLAGS)  -c $< -o $(<:.c=.o) 

$(NAME): $(OBJ)
	 $(AR) $(NAME) $(OBJ)

bonus:  $(OBJBONUS)
	$(AR) $(NAME) $(OBJBONUS)

clean:
	rm -f *.o a.out

fclean: clean
	rm -f $(NAME)

re: fclean all
