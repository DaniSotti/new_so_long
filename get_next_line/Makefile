# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/05 16:17:04 by dde-sott          #+#    #+#              #
#    Updated: 2023/08/05 16:22:09 by dde-sott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a

SRC = get_next_line \
	get_next_line_utils

CC = gcc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -I.

all:$(NAME)

$(NAME): $(SRC:=.o)
			ar rc $(NAME) $(SRC:=.o)
clean:
	$(RM) $(SRC:=.o)
fclean: clean
	$(RM) $(NAME)
re: fclean $(NAME)
bonus: $(SRC:=.o)
		ar rc $(NAME) $(SRC:=.o)
