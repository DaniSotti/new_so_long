/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:52:49 by dde-sott          #+#    #+#             */
/*   Updated: 2023/10/15 18:52:49 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	create_map(t_data *data)
{
	char	*line;
	int		i;
	int		fd;

	data->map = (char **)malloc((data->map_height + 1) * sizeof(char *));
	if (!data->map)
		exit (1);
	fd = open_map_file(data);
	i = 0;
	line = get_next_line(fd);
	while (i < data->map_height && (line))
	{
		data->map[i] = ft_strdup(line);
		free(line);
		if (!data->map[i])
			exit (1);
		i++;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	data->map[i] = NULL;
}

void	create_dup_map(t_data *data)
{
	char	*line;
	int		i;
	int		fd;

	data->temp_map = (char **)malloc((data->map_height + 1) * sizeof(char *));
	if (!data->temp_map)
		exit (1);
	fd = open_map_file(data);
	i = 0;
	line = get_next_line(fd);
	while (i < data->map_height && (line))
	{
		data->temp_map[i] = ft_strdup(line);
		free(line);
		if (!data->temp_map[i])
			exit (1);
		i++;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	data->temp_map[i] = NULL;
}

int	draw_map(t_data *data)
{
	int		i;
	int		j;
	char	cell;

	i = -1;
	while (++i < data->map_height)
	{
		j = -1;
		while (++j < data->map_width)
		{
			cell = data->map[i][j];
			if (cell == '1')
				draw_image(data, WALL, j, i);
			else if (cell == 'E')
				draw_image(data, EXIT_CLOSED, j, i);
			else if (cell == 'C')
				draw_image(data, ALGAE, j, i);
			else
				draw_image(data, FLOOR, j, i);
		}
	}
	draw_image(data, PLAYER_FRONT, data->player_x,
		data->player_y);
	return (0);
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
					draw_image(data, EXIT_OPEN, j, i);
			}
			j++;
		}
		i++;
	}
}
