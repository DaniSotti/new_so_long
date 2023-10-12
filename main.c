/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:05:05 by dde-sott          #+#    #+#             */
/*   Updated: 2023/09/04 20:05:05 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_clean_map(t_data *data)
{
	int	i;

	i = 0;
	if (data->map != NULL)
	{
		while (i < data->map_height)
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}

	if (data->temp_map != NULL)
	{
		while (i < data->map_height)
		{
			free(data->temp_map[i]);
			i++;
		}
		free(data->temp_map);
	}

	if (data->map_path)
	{
		free(data->map_path);
	}

	if (data->mlx) {
		mlx_clear_window(data->mlx, data->win);
        mlx_destroy_window(data->mlx, data->win);
        mlx_destroy_display(data->mlx);
		free(data->mlx);
    }
	// free(data->mlx);
	// if (data->map_path != NULL)
	// {
	// 	free(data->map_path);
	// }
}

void	draw_image(t_data *data, char *image_path, int x, int y)
{
	int		img_width;
	int		img_height;
	void	*image;

	image = mlx_xpm_file_to_image(data->mlx, image_path,
			&img_width, &img_height);
	mlx_put_image_to_window(data->mlx, data->win, image,
		x * TILE_SIZE, y * TILE_SIZE);
	mlx_destroy_image(data->mlx, image);
}

void	render_moves(t_data *data)
{
	char	*moves_str;
	int		moves_str_width;
	int		moves_x;
	int		moves_y;
	char	*prev_mov_char;	

	moves_str_width = ft_strlen("Moves:") * 10;
	moves_x = (data->map_width * TILE_SIZE - moves_str_width) / 2;
	moves_y = data->map_height * TILE_SIZE + (BLACK_BAR_HEIGHT / 2);
	prev_mov_char = ft_itoa(data->prev_mov_int);
	mlx_string_put(data->mlx, data->win, moves_x + moves_str_width + 10,
		moves_y, 0x000000, prev_mov_char);
	mlx_string_put(data->mlx, data->win, moves_x, moves_y, 0xFFFFFF, "Moves:");
	moves_str = ft_itoa(data->moves);
	data->prev_mov_int = data->moves;
	if (data->prev_mov_int > 0)
		ft_printf("MOVES: %d\n", data->moves);
	data->moves++;
	mlx_string_put(data->mlx, data->win, moves_x + moves_str_width + 10,
		moves_y, 0xFFFFFF, moves_str);
	free(moves_str);
	free(prev_mov_char);
}

int	draw_map(t_data *data)
{
	int		i;
	int		j;
	char	cell;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			cell = data->map[i][j];
			if (cell == '1')
				draw_image(data, "./images/new_wall6.xpm", j, i);
			else if (cell == 'E')
				draw_image(data, "./images/exit_closed.xpm", j, i);
			else if (cell == 'C')
				draw_image(data, "./images/algae_big_resized.xpm", j, i);
			else
				draw_image(data, "./images/floor_resized.xpm", j, i);
			j++;
		}
		i++;
	}
	draw_image(data, "./images/tardigrade_front.xpm", data->player_x,
		data->player_y);
	return (0);
}

int	check_game_state(t_data *data)
{
	int	i;
	int	j;
	int	count_algae;

	count_algae = 0;
	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (data->map[i][j] == 'C')
				count_algae++;
			j++;
		}
		i++;
	}
	return (count_algae);
}

void	draw_new_exit(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (i < data->map_height && j < data->map_width)
			{
				if (data->map[i][j] == 'E')
					draw_image(data, "./images/exit_open1.xpm", j, i);
			}
			j++;
		}
		i++;
	}
}

int	exit_game(t_data *data)
{
	ft_printf("Ohhh! You gave up :( \n");
	ft_clean_map(data);
	exit(EXIT_SUCCESS);
}

void	calculate_next_position(int keycode, t_data *data)
{
	if (keycode == KEY_UP || keycode == KEY_W)
		data->next_y--;
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		data->next_y++;
	else if (keycode == KEY_LEFT || keycode == KEY_A)
	{
		data->next_x--;
		data->player_direction = KEY_LEFT;
	}
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
	{
		data->next_x++;
		data->player_direction = KEY_RIGHT;
	}
}

int	is_valid_move(int keycode, t_data *data)
{
	if (keycode != KEY_UP && keycode != KEY_DOWN
		&& keycode != KEY_LEFT && keycode != KEY_RIGHT
		&& keycode != KEY_A && keycode != KEY_S
		&& keycode != KEY_D && keycode != KEY_W
		&& keycode != KEY_ESC)
		return (0);
	return (data->map[data->next_y][data->next_x] != '1' &&
		data->map[data->next_y][data->next_x] != 'E');
}

void	clear_update_position(t_data *data)
{
	if (data->map[data->next_y][data->next_x] == 'C')
		data->map[data->next_y][data->next_x] = '0';
	draw_image(data, "./images/floor_resized.xpm", data->player_x,
		data->player_y);
	data->player_x = data->next_x;
	data->player_y = data->next_y;
	if (data->player_direction == KEY_RIGHT)
		draw_image(data, "./images/tardigrade_right.xpm",
			data->player_x, data->player_y);
	else if (data->player_direction == KEY_LEFT)
		draw_image(data, "./images/tardigrade_left.xpm",
			data->player_x, data->player_y);
	else
		draw_image(data, "./images/tardigrade_front.xpm",
			data->player_x, data->player_y);
	data->player_direction = 0;
}

int	handle_keypress(int keycode, t_data *data)
{
	data->next_x = data->player_x;
	data->next_y = data->player_y;
	data->next_x = data->player_x;
	data->next_y = data->player_y;
	if (keycode == KEY_ESC)
		exit_game(data);
	calculate_next_position(keycode, data);
	if (is_valid_move(keycode, data))
	{
		render_moves(data);
		clear_update_position(data);
		if (check_game_state(data) == 0)
			draw_new_exit(data);
	}
	if (check_game_state(data) == 0)
	{
		if (data->map[data->next_y][data->next_x] == 'E')
		{
			ft_printf("MOVES: %d\n", data->moves);
			ft_printf("You win :) \n");
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}

void	is_map_surrounded_by_walls(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_height)
	{
		if ((data->map[i][0] != '1') 
			|| (data->map[i][data->map_width - 1] != '1'))
		{
			ft_printf("The map is not surrounded by walls.\n");
			exit (EXIT_FAILURE);
		}
		i++;
	}
	j = 0;
	while (j < data->map_width)
	{
		if ((data->map[0][j] != '1') || (data->map[data->map_height - 1][j] != '1'))
		{
			ft_printf("The map is not surrounded by walls.\n");
			exit (EXIT_FAILURE);
		}
		j++;
	}
}

// int	check_line_length(t_data *data)
// {
// 	int	i;
// 	int	line_length;
// 	int	expected_line_length;

// 	i = 0;
// 	expected_line_length = data->map_width;
// 	while (i < data->map_height)
// 	{
// 		line_length = ft_strlen(data->map[i]);
// 		if (line_length != expected_line_length)
// 		{
// 			ft_printf("O erro sai daqui");
// 			ft_printf("%d\n", line_length);
// 			ft_printf("%d\n", expected_line_length);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

static void	check_counts(t_data *data, int height, int width)
{
	if (data->map[height][width] != '1' &&
		data->map[height][width] != '0' &&
		data->map[height][width] != 'P' &&
		data->map[height][width] != 'E' &&
		data->map[height][width] != 'C' &&
		data->map[height][width] != '\n')
	{
		ft_printf("There are different map caracteres.\n");
		// ft_clean_map(data, data->map);
		exit (EXIT_FAILURE);
	}
	if (data->map[height][width] == 'C')
		data->collectible_count++;
	if (data->map[height][width] == 'P')
		data->player_count++;
	if (data->map[height][width] == 'E')
		data->exit_count++;
}

void	valid_character(t_data *data)
{
	int	height;
	int	width;

	height = 0;
	data->player_count = 0;
	data->exit_count = 0;
	data->collectible_count = 0;
	while (height < data->map_height - 1)
	{
		width = 0;
		while (width < data->map_width)
		{
			check_counts(data, height, width);
			width++;
		}
		height++;
	}
	if ((data->player_count != 1 || data->exit_count != 1
			|| data->collectible_count == 0))
	{
		ft_printf("%d, %d, %d", data->map_height, data->exit_count, data->collectible_count);
		ft_printf("Something wrong.\n");
		// ft_clean_map(data, data->map);
		exit (EXIT_FAILURE);
	}
}

//Na escola nao precisa fazer esta validacao
// if (line[line_length] == '\n')
		// 	line_length--;



void	count_size_map(t_data *data)
{
	char	*line;
	int		line_length;

	line_length = 0;
	data->map_width = 0;
	data->map_height = 0;
	line = get_next_line(data->fd);
	while (line)
	{
		while (line[line_length] != '\0' && line[line_length] != '\n')
			line_length++;
		if (line[line_length] == '\n')
		 	line_length--;
		if (data->map_width > 0 && line_length != data->map_width)
		{
			ft_printf("Map Error \n");
			// ft_clean_map(data, data->map);
			exit(EXIT_FAILURE);
		}
		data->map_width = line_length;
		data->map_height++;
		free(line);
		line = get_next_line(data->fd);
	}
	free(line);
}

char	**create_map(t_data *data)
{
	char	**map;
	char	*line;
	int		i;

	map = (char **)malloc((data->map_height + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	data->fd = open(data->map_path, O_RDONLY);
	i = 0;
	line = get_next_line(data->fd);
	while (i < data->map_height && (line))
	{
		map[i] = ft_strdup(line);
		free(line);
		if (!map[i])
			return (NULL);
		i++;
		line = get_next_line(data->fd);
	}
	free(line);
	close(data->fd);
	map[i] = NULL;
	return (map);
}

void	player_initial_position(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (data->map[i][j] == 'P')
			{
				data->player_x = j;
				data->player_y = i;
				break ;
			}
			j++;
		}
		i++;
	}
}

void	mark_path(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height
		|| data->temp_map[y][x] == 'V')
		return ;
	if (data->temp_map[y][x] == 'C')
		data->collectible_count--;
	else if (data->temp_map[y][x] == 'E')
		data->exit_count--;
	data->temp_map[y][x] = 'V';
	check_path(data, x + 1, y);
	check_path(data, x - 1, y);
	check_path(data, x, y + 1);
	check_path(data, x, y - 1);
}

void	check_path(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height)
		return ;
	if (data->map[y][x] == 'P' || data->map[y][x] == 'E'
	|| data->map[y][x] == 'C' || data->map[y][x] == '0')
		mark_path(data, x, y);
}

// int open_map_file(char *map_name, char **map_path) {
//     char *s = ft_strjoin("maps/", map_name);
//     *map_path = ft_strjoin(s, ".ber");
//     free(s);

//     int fd = open(*map_path, O_RDONLY);
//     if (fd == -1) {
//         ft_printf("Error opening the map file.\n");
//         exit(1);
//     }
//     return fd;
// }

void	init_game(t_data *data, char *map_name)
{
	char	*s;

	data->player_x = 0;
	data->player_y = 0;
	data->moves = 0;
	data->prev_mov_int = 0;
	s = ft_strjoin("maps/", map_name);
	data->map_path = ft_strjoin(s, ".ber");
	free(s);
	if (data->map_path == NULL)
	{
		ft_printf("Error creating map path\n");
		// free(data->map_path);
		exit (EXIT_FAILURE);
	}
	data->fd = open(data->map_path, O_RDONLY);
	if (data->fd == -1)
	{
		ft_printf("Error opening the map file.\n");
		close(data->fd);
		free(data->map_path);
		exit (EXIT_FAILURE);
	}
}

void	check_elements(t_data *data)
{
	valid_character(data);
	is_map_surrounded_by_walls(data);
	
	check_path(data, data->player_x, data->player_y);
	if (data->exit_count != 0 || data->collectible_count != 0)
	{
		ft_printf("Player blocked.\n");
		// ft_clean_map(data);
		exit (EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_printf("you need to choose the map name \n");
		return (1);
	}
	init_game(&data, argv[1]);
	count_size_map(&data);
	data.map = create_map(&data);
	player_initial_position(&data);
	data.temp_map = create_map(&data);
	check_elements(&data);
	data.mlx = mlx_init();
	data.win_w = data.map_width * TILE_SIZE;
	data.win_h = data.map_height * TILE_SIZE;
	data.win = mlx_new_window(data.mlx, data.win_w, data.win_h + BLACK_BAR_HEIGHT, "So Long");
	render_moves(&data);
	//draw_map(&data);
	mlx_hook(data.win, 2, 1L << 0, handle_keypress, &data);
	mlx_hook(data.win, 17, 1L << 0, exit_game, &data);
	mlx_hook(data.win, 12, 1L << 15, draw_map, &data);
	mlx_loop(data.mlx);
	ft_clean_map(&data);
	return (0);
}

	// mlx_destroy_window(data.mlx, data.win); 
	// mlx_destroy_display(data.mlx);            
