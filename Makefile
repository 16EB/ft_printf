# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 12:08:12 by jkong             #+#    #+#              #
#    Updated: 2022/03/17 17:27:35 by jkong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re bonus

CC = gcc
CFLAGS = -I. -Wall -Wextra -Werror
RM = rm -f
AR = ar
ARFLAGS = crs

NAME = libftprintf.a
INCS = libftprintf.h
SRCS = format.c ftprintf.c libft.c stream.c stream_integer.c util_flag.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $?

bonus: all

$(OBJS): $(INCS)
