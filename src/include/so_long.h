/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:27:23 by dde-sott          #+#    #+#             */
/*   Updated: 2023/07/08 12:27:23 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx_linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../libft/incs/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../ft_printf/ft_printf.h"

# define TILE_SIZE 32
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_W 119
# define KEY_ESC 65307
# define BLACK_BAR_HEIGHT 30

//images xpm
# define WALL "./images/wall.xpm"
# define EXIT_CLOSED "./images/exit_closed.xpm"
# define EXIT_OPEN "./images/exit_open.xpm"
# define ALGAE "./images/algae.xpm"
# define FLOOR "./images/floor.xpm"
# define PLAYER_FRONT "./images/tardigrade_front.xpm"
# define PLAYER_RIGHT "./images/tardigrade_right.xpm"
# define PLAYER_LEFT "./images/tardigrade_left.xpm"

typedef struct s_data {
	void	*mlx;
	void	*win;
	char	**map;
	char	**temp_map;
	int		map_width;
	int		map_height;
	int		length;
	int		collectible_count;
	int		exit_count;
	int		player_count;
	int		player_direction;
	int		player_x;
	int		player_y;
	int		next_x;
	int		next_y;
	int		fd;
	char	*map_path;
	int		moves;
	int		prev_mov_int;
}	t_data;

//utils functions
void	ft_clean_map(t_data *data);
void	ft_clean_window(t_data *data);
int		exit_game(t_data *data);
void	count_size_map(t_data *data);
int		open_map_file(t_data *data);

//map functions
void	create_map(t_data *data);
void	create_dup_map(t_data *data);
int		draw_map(t_data *data);
void	draw_image(t_data *data, char *image_path, int x, int y);
void	draw_new_exit(t_data *data);

//movements functions
void	render_moves(t_data *data);
void	calculate_next_position(int keycode, t_data *data);
int		is_valid_move(int keycode, t_data *data);
void	clear_update_position(t_data *data);
int		handle_keypress(int keycode, t_data *data);

//check functions
void	is_map_surrounded_by_walls(t_data *data);
void	check_counts(t_data *data, int height, int width);
int		check_game_state(t_data *data);
void	valid_character(t_data *data);
void	check_elements(t_data *data);

//utils 2
void	create_window(t_data *data);
void	mark_path(t_data *data, int x, int y);
void	check_path(t_data *data, int x, int y);

void	player_initial_position(t_data *data);
void	init_game(t_data *data, char *map_name);

#endif