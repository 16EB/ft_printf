# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 12:08:12 by jkong             #+#    #+#              #
#    Updated: 2022/03/17 12:08:52 by jkong            ###   ########.fr        #
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
SRCS_BONUS = 
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $?

bonus: $(OBJS_BONUS)
	$(AR) $(ARFLAGS) $(NAME) $?

$(OBJS): $(INCS)

$(OBJS_BONUS): $(INCS)
