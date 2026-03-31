# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 14:41:02 by fadzejli          #+#    #+#              #
#    Updated: 2026/03/31 20:47:21 by macarnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc -Wall -Wextra -Werror -g -MMD -MP
SRCS = ft_isalpha.c \
	ft_strlcat.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_isdigit.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_strmapi.c \
	ft_itoa.c \
	ft_striteri.c \
	ft_split.c \
	ft_atoi.c \
	ft_strtrim.c \
	ft_strnstr.c \
	ft_is_empty.c \
	ft_isspace.c \
	gnl.c	\
	ft_atoi_rgb.c \
	ft_free_split.c \
	ft_strcmp.c \
	ft_strtol.c
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)
INC = libft.h

all : $(NAME)

%.o : %.c $(INC)
	$(CC) -I. -c $< -o $@

$(NAME): $(OBJS) $(INC)
	ar rcs $(NAME) $(OBJS)

clean :
	rm -rf $(OBJS)
	rm -rf $(DEPS)

fclean : clean
	rm -rf $(NAME)

re : clean fclean all

.PHONY: clean fclean re

 -include $(DEPS)