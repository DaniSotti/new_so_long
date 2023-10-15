/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:00:08 by dde-sott          #+#    #+#             */
/*   Updated: 2023/10/15 19:00:08 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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
	draw_image(data, FLOOR, data->player_x,
		data->player_y);
	data->player_x = data->next_x;
	data->player_y = data->next_y;
	if (data->player_direction == KEY_RIGHT)
		draw_image(data, PLAYER_RIGHT,
			data->player_x, data->player_y);
	else if (data->player_direction == KEY_LEFT)
		draw_image(data, PLAYER_LEFT,
			data->player_x, data->player_y);
	else
		draw_image(data, PLAYER_FRONT,
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
			ft_clean_map(data);
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}
