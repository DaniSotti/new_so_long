# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/08 12:29:39 by dde-sott          #+#    #+#              #
#    Updated: 2023/07/08 12:29:39 by dde-sott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the project
NAME = so_long

# Compiler
CC = cc
CC_FLAGS = -Wall -Wextra -Werror
MLXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 

# -fsanitize=address

MLX_LINUX = -I/usr/include -Imlx_linux -O3

# .c files
SOURCE = src/main src/utils src/map src/moves src/check src/utils2

# Transform .c files to .o files
C_SOURCE = $(SOURCE:%=%.c)

# Object files
O_FILES = $(C_SOURCE:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

GNL_DIR = get_next_line
GNL_SRCS = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c

PRTF_DIR = ft_printf
PRTF_SRCS = $(PRTF_DIR)/ft_printf.c $(PRTF_DIR)/ft_numbers.c \
$(PRTF_DIR)/ft_putchar.c $(PRTF_DIR)/ft_putstr.c

all: $(LIBFT) $(NAME)

%.o: %.c
	$(CC) $(CC_FLAGS) $(MLX_LINUX) -c $< -o $@

$(NAME): $(O_FILES) $(LIBFT)
	$(CC) $(CC_FLAGS) $(O_FILES) $(GNL_SRCS) $(PRTF_SRCS) $(MLXFLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(O_FILES)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
