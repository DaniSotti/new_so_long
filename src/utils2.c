/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:34:54 by dde-sott          #+#    #+#             */
/*   Updated: 2023/10/15 19:34:54 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

void	create_window(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->map_width * TILE_SIZE,
			data->map_height * TILE_SIZE + BLACK_BAR_HEIGHT, "So Long");
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
