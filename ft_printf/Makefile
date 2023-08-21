# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/01 22:50:04 by dde-sott          #+#    #+#              #
#    Updated: 2022/12/12 23:49:30 by dde-sott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Name of the project
NAME = libftprintf.a

#.c files
SOURCE = ft_printf ft_putstr \
		 ft_numbers ft_putchar \
		 
#transformar os ficheiros em ficheiro .c
C_SOURCE = $(SOURCE:%=%.c)

#Object files para transformar todos os ficheiros .c para .o?
O_FILES = $(C_SOURCE:.c=.o)

#Compiler
CC = cc
CC_FLAGS = -Wall\
           -Werror\
           -Wextra

all: $(NAME)

$(NAME):
	$(CC) $(CC_FLAGS) -c $(C_SOURCE) -I./
	ar -rc $(NAME) $(O_FILES)

clean:
	rm -f $(O_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)