# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/01 19:21:05 by dde-sott          #+#    #+#              #
#    Updated: 2023/08/05 16:35:42 by dde-sott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Name of the project
NAME = libft.a

#.c files
SOURCE = ft_strlen ft_isalnum ft_isalpha \
           ft_isascii ft_isdigit ft_isprint \
           ft_memcpy ft_memset ft_strlcpy \
           ft_strlen ft_strlcat ft_strrchr \
           ft_atoi ft_memmove ft_bzero \
           ft_calloc ft_memchr ft_memcmp \
           ft_strchr ft_strdup ft_strjoin \
           ft_strncmp ft_substr ft_tolower \
           ft_toupper ft_putchar_fd ft_putstr_fd \
           ft_putendl_fd ft_putnbr_fd ft_strtrim \
           ft_strnstr ft_itoa ft_strmapi ft_striteri \
           ft_split

BONUS = ft_lstnew ft_lstadd_front ft_lstsize \
        ft_lstlast ft_lstadd_back ft_lstdelone \
        ft_lstclear ft_lstiter ft_lstmap

#transformar os ficheiros em ficheiro .c
C_SOURCE = $(SOURCE:%=%.c)

#buscar os ficheiro bonus .c
C_BONUS = $(BONUS:%=%.c)
#transforma os ficheiro bonus .c em .o
O_BONUS = $(C_BONUS:.c=.o)
#Object files para transformar todos os ficheiros .c para .o?
O_FILES = $(C_SOURCE:.c=.o)

#Compiler
CC = cc
CC_FLAGS = -Wall -Werror -Wextra -g -I incs

all: $(NAME)

$(NAME):
	$(CC) $(CC_FLAGS) -c $(C_SOURCE) -I./
	ar -rc $(NAME) $(O_FILES)

bonus:	$(C_BONUS)
			$(CC) $(CC_FLAGS) -c $(C_BONUS) -I./
			ar -rc $(NAME) $(O_BONUS)

clean:
	rm -f $(O_FILES)
	rm -f $(O_BONUS)
fclean: clean
	rm -f $(NAME)
re: fclean $(NAME)
