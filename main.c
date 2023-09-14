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

#include "mlx_linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "so_long.h"
#include "libft/incs/libft.h"
// #include "get_next_line/get_next_line.h"

#define TILE_SIZE 32
#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_W 119
#define KEY_ESC 65307
#define BLACK_BAR_HEIGHT 30
// # define PLAYER "./images/tardigrade.xpm"

typedef struct s_data {
	void	*mlx;
	void	*win;
	char	**map;
	int		player_x;
	int		player_y;
	int		map_width;
	int		map_height;
	int		fd;
	char	*map_path;
	int		moves;
	int		next_x;
	int		next_y;
	int		player_direction;
	int		prev_mov_int;
	int		collectible_count;
	int		exit_count;
	int		player_count;
	int		exit;
	int		collectibles;
	char	**temp_map;
}	t_data;

// void	draw_player(t_data *data)
// {
//     int		img_width;
//     int		img_height;
// 	void	*tardigrade;	
// 	tardigrade = mlx_xpm_file_to_image(data->mlx, PLAYER, 
//					&img_width, &img_height);
//  mlx_put_image_to_window(data->mlx, data->win, tardigrade, 
//					data->player_x *TILE_SIZE, data->player_y * TILE_SIZE);
// }

 int is_collectible_blocked(t_data *data, int x, int y) {
 	//Eu vou na posicao pra cima pra baixo e para os lados verificando se tenho 1 e retorno erro caso sim
     return (x > 0 && data->map[y][x - 1] == '1') &&
            (x < data->map_width - 1 && data->map[y][x + 1] == '1') &&
            (y > 0 && data->map[y - 1][x] == '1') &&
            (y < data->map_height - 1 && data->map[y + 1][x] == '1');
 }

int is_exit_blocked(t_data *data, int x, int y) {
 	 return (x > 0 && data->map[y][x - 1] == '1') &&
            (x < data->map_width - 1 && data->map[y][x + 1] == '1') &&
            (y > 0 && data->map[y - 1][x] == '1') &&
            (y < data->map_height - 1 && data->map[y + 1][x] == '1');
 }

//  int check_exit_collectibles(t_data *data) {
//     int player_count = 0;
//     int exit_count = 0;
//     int collectible_count = 0;
//     int expected_line_length = data->map_width;

//     int i = 0;
//     while (i < data->map_height) {
//         int line_length = ft_strlen(data->map[i]);

//         if (line_length != expected_line_length) {
//             ft_printf("Line %d has an incorrect length. Expected: %d, Found: %d.\n", i + 1, expected_line_length, line_length);
//             return 0;
//         }

//         int j = 0;
//         while (j < data->map_width) {
//             char cell = data->map[i][j];
//             if (cell != 'P' && cell != '1' && cell != 'C' && cell != 'E' && cell != '0' && cell != '\n')
//             {
//                 ft_printf("There are different map caracteres.\n");
//                 return 0;
//             }
//             if (cell == 'P') {
//                 player_count++;
//             } else if (cell == 'E') {
//                 exit_count++;
// 				if (is_exit_blocked(data, j, i)) {
//                      ft_printf("Exit at (%d, %d) is completely blocked by walls.\n", i, j);
//                      return 0;
//                 }
//             } else if (cell == 'C') {
//                 collectible_count++;

//                 // Check for collectibles blocked by walls
//                  if (is_collectible_blocked(data, j, i)) {
//                      ft_printf("Collectible at (%d, %d) is completely blocked by walls.\n", i, j);
//                      return 0;
//                  }
//             }
//             j++;
//         }
//         i++;
//     }
//     return 1;
// }

void	draw_image(t_data *data, char *image_path, int x, int y)
{
	int		img_width;
	int		img_height;
	void	*image;

	image = mlx_xpm_file_to_image(data->mlx, image_path,
			&img_width, &img_height);
	mlx_put_image_to_window(data->mlx, data->win, image,
		x * TILE_SIZE, y * TILE_SIZE);
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
	mlx_string_put(data->mlx, data->win, moves_x + moves_str_width + 10,
		moves_y, 0xFFFFFF, moves_str);
	free(moves_str);
	free(prev_mov_char);
}

void	draw_map(t_data *data)
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

void	exit_game(t_data *data)
{
	ft_printf("Ohhh! You gave up :( \n");
	free (data->map);
	exit (0);
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

void	update_moves(t_data *data)
{
	data->moves++;
	ft_printf("MOVES: %d\n", data->moves);
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
		update_moves(data);
		render_moves(data);
		clear_update_position(data);
		if (check_game_state(data) == 0)
			draw_new_exit(data);
	}
	if (check_game_state(data) == 0)
	{
		if (data->map[data->next_y][data->next_x] == 'E')
		{
			ft_printf("You win :) \n");
			exit(0);
		}
	}
	return (0);
}

int	is_wall(char **map, int x, int y)
{
	return (map[y][x] == '1');
}

int	is_map_surrounded_by_walls(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_height)
	{
		if (!is_wall(data->map, 0, i) || !is_wall(data->map,
				data->map_width - 1, i))
			return (0);
		i++;
	}
	j = 0;
	while (j < data->map_width)
	{
		if (!is_wall(data->map, j, 0) || !is_wall(data->map, j,
				data->map_height - 1))
			return (0);
		j++;
	}
	return (1);
}

int	check_line_length(t_data *data)
{
	int	i;
	int	line_length;
	int	expected_line_length;

	i = 0;
	expected_line_length = data->map_width;
	while (i < data->map_height)
	{
		line_length = ft_strlen(data->map[i]);
		if (line_length != expected_line_length)
		{
			ft_printf("Map Error \n");
			return (1);
		}
		i++;
	}
	return (0);
}

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
		exit (1);
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
		ft_printf("Something wrong.\n");
		exit (1);
	}
}

int	check_elements(t_data *data)
{
	check_line_length(data);
	valid_character(data);
	if (!is_map_surrounded_by_walls(data))
	{
		ft_printf("The map is not surrounded by walls.\n");
		return (0);
	}
	return (1);
}

void	check_map(t_data *data)
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
			exit(1);
		}
		data->map_width = line_length;
		data->map_height++;
		free(line);
		line = get_next_line(data->fd);
	}
}

void	create_map(t_data *data)
{
	char	*line;
	int		i;
	int		j;

	data->map = (char **)malloc(data->map_height * sizeof(char *));
	i = 0;
	while (i < data->map_height)
		data->map[i++] = (char *)malloc(data->map_width * sizeof(char));
	data->fd = open(data->map_path, O_RDONLY);
	i = 0;
	line = get_next_line(data->fd);
	while (line)
	{
		j = 0;
		while (j < data->map_width)
		{
			data->map[i][j] = line[j];
			j++;
		}
		data->map[i][j] = '\0';
		free(line);
		i++;
		line = get_next_line(data->fd);
	}
	close(data->fd);
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

int	handle_window_close(t_data *data)
{
	ft_printf("Ohhh! You gave up :(\n");
	free(data->map);
	exit(0);
	return (0);
}

int	handle_expose(t_data *data)
{
	draw_map(data);
	return (0);
}

void	ft_clean_map(t_data *data, char **map)
{
	int	i;

	i = 0;
	while (i < data->map_height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void clone_map(t_data *data)
{
   	char	*line;
	int		i;
	int		j;

	data->temp_map = (char **)malloc(data->map_height * sizeof(char *));
	i = 0;
	while (i < data->map_height)
		data->temp_map[i++] = (char *)malloc(data->map_width * sizeof(char));
	data->fd = open(data->map_path, O_RDONLY);
	i = 0;
	line = get_next_line(data->fd);
	while (line)
	{
		j = 0;
		while (j < data->map_width)
		{
			data->temp_map[i][j] = line[j];
			j++;
		}
		data->temp_map[i][j] = '\0';
		free(line);
		i++;
		line = get_next_line(data->fd);
	}
	close(data->fd);
}

// int can_reach_point(t_data *data, int x, int y) {
//     if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height)
// 	{
//          // Fora dos limites do mapa
//          return 0;
//  	}
    
//     char cell = data->temp_map[y][x];
//     // if (cell == '1')
// 	// {
//     //     // A parede bloqueia o caminho
//     //     // return 0;
//     // } else 
// 	if (cell == 'C')
// 	{
//         // Coletou um colecionável
//         // data->temp_map[y][x] = '0';
//         data->collectibles--;
// 	} else if (cell == 'E')
// 	{
//          // Chegou à saída
//          return 1;
//     }

//     // Tenta alcançar os pontos vizinhos
//     int can_reach = can_reach_point(data, x + 1, y) ||
//                     can_reach_point(data, x - 1, y) ||
//                     can_reach_point(data, x, y + 1) ||
//                     can_reach_point(data, x, y - 1);

//     return can_reach;
// }

// // Função para verificar se o jogador pode alcançar todos os colecionáveis e a saída
// int can_reach_collectibles_and_exit(t_data *data)
// {
// 	data->collectibles = data->collectible_count;
//     int x = data->player_x;
//     int y = data->player_y;
//     // Verifique se o jogador pode alcançar todos os colecionáveis e a saída a partir da posição atual
//     return can_reach_point(data, x, y) && data->collectibles == 0;
// }


void	mark_path(t_data *data, int x, int y);
void check_path(t_data *data, int x, int y);

void mark_path(t_data *data, int x, int y)
{
    if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height || data->temp_map[y][x] == 'V') 
          return; // Saia se estivermos fora dos limites do mapa.

    char cell = data->temp_map[y][x];
	 
    //  if (cell == 'P')
    //     data->temp_map[y][x] = 'p';
     if (cell == 'C')
        data->collectible_count--;
     else if (cell == 'E')
         data->exit_count--;
	data->temp_map[y][x] = 'V';
	check_path(data, x + 1, y);
	check_path(data, x - 1, y);
	check_path(data, x, y + 1);
	check_path(data, x, y - 1);
 }

 void check_path(t_data *data, int x, int y)
 {
     if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height)
         return; // Saia se estivermos fora dos limites do mapa.

     char cell = data->map[y][x];
     if (cell == 'P' || cell == 'E' || cell == 'C' || cell == '0')
     {
         mark_path(data, x, y);
		 ft_printf("%c \n", cell);
     }
 }




int main(int argc, char **argv)
{
	t_data	data;

	data.player_x = 0;
	data.player_y = 0;
	data.moves = 0;
	data.prev_mov_int = 0;
	if (argc != 2)
	{
		ft_printf("you need to choose the map name \n");
		exit(1);
	}
	data.map_path = ft_strjoin("maps/", argv[1]);
	data.map_path = ft_strjoin(data.map_path, ".ber");
	data.fd = open(data.map_path, O_RDONLY);
	if (data.fd == -1)
	{
		perror("Error opening the map file");
		return (1);
	}
	check_map(&data);
	close(data.fd);
	create_map(&data);
	player_initial_position(&data);
	if (!check_elements(&data))
        return (1);
	// if (!check_exit_collectibles(&data))
    //     return (1);
	  // Verifique se o jogador pode alcançar todos os colecionáveis e a saída
	clone_map(&data);
    // int result = can_reach_collectibles_and_exit(&data);

    // if (result) {
    //     printf("O jogador pode alcançar todos os colecionáveis e a saída.\n");
    // } else {
    //     printf("O jogador não pode alcançar todos os colecionáveis e/ou a saída.\n");
    // }
	// Chama check_path para verificar se o jogador pode alcançar todos os colecionáveis e a saída
	 check_path(&data, data.player_x, data.player_y);

	 if (data.exit_count != 0 || data.collectible_count != 0) {
		ft_printf("%d \n",data.exit);
		ft_printf("%d \n",data.collectibles);
	 	ft_printf("O jogador não pode alcançar todos os colecionáveis e/ou a saída.\n");
	 	ft_clean_map(&data, data.temp_map);
	 	return 1;
	 }
	
	// if (!can_reach_all_points(&data, data.player_x, data.player_y)) {
    // 	ft_printf("O jogador não pode alcançar todos os colecionáveis e/ou a saída.\n");
    // 	ft_clean_map(&data, data.temp_map);
    // 	return 1;
	// }	
	// check_path(&data, data.player_x, data.player_y);
	// if (!can_reach_collectibles_and_exit(&data, data.player_x, data.player_y))
    // {
    //     ft_printf("O jogador não pode alcançar todos os colecionáveis e/ou a saída.\n");
    //     ft_clean_map(&data);
    //     return 1;
    // }
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.map_width * TILE_SIZE,
			(data.map_height * TILE_SIZE) + BLACK_BAR_HEIGHT, "So Long");
	render_moves(&data);
	mlx_hook(data.win, 2, 1L << 0, handle_keypress, &data);
	mlx_hook(data.win, 17, 1L << 0, handle_window_close, &data);
	mlx_hook(data.win, 12, 1L << 15, handle_expose, &data);
	mlx_loop(data.mlx);
	draw_map(&data);
	ft_clean_map(&data, data.map);
	return (0);
}
