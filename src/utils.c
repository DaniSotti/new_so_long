/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:42:40 by dde-sott          #+#    #+#             */
/*   Updated: 2023/10/15 18:42:40 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ft_clean_window(t_data *data)
{
	if (data->mlx)
	{
		mlx_clear_window(data->mlx, data->win);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

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
	i = 0;
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
		free(data->map_path);
	ft_clean_window(data);
}

int	exit_game(t_data *data)
{
	ft_printf("Ohhh! You gave up :( \n");
	ft_clean_map(data);
	exit(EXIT_SUCCESS);
}

//Na escola nao precisa fazer esta validacao
// if (line[line_length] == '\n')
		// 	line_length--;

void	count_size_map(t_data *data)
{
	char	*line;
	int		fd;

	fd = open_map_file(data);
	line = get_next_line(fd);
	while (line)
	{
		data->length = 0;
		while (line[data->length] != '\0' && line[data->length] != '\n')
			data->length++;
		if (line[data->length] == '\n')
			data->length--;
		if (data->map_width > 0 && data->length != data->map_width)
		{
			free(line);
			ft_clean_map(data);
			ft_printf("There is a problem with the Map size. \n");
			close(fd);
			exit(EXIT_FAILURE);
		}
		data->map_width = data->length;
		data->map_height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

int	open_map_file(t_data *data)
{
	int	fd;

	fd = open(data->map_path, 0, O_RDONLY);
	if (fd < 0)
	{
		if (data->map_path)
			free(data->map_path);
		ft_printf("Error opening the map file.\n");
		exit(1);
	}
	return (fd);
}
