/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:28:28 by dde-sott          #+#    #+#             */
/*   Updated: 2023/10/15 19:28:28 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

void	is_map_surrounded_by_walls(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map_height)
	{
		if ((data->map[i][0] != '1')
			|| (data->map[i][data->map_width - 1] != '1'))
		{
			ft_clean_map(data);
			ft_printf("The map is not surrounded by walls.\n");
			exit (EXIT_FAILURE);
		}
	}
	j = -1;
	while (++j < data->map_width)
	{
		if ((data->map[0][j] != '1')
		|| (data->map[data->map_height - 1][j] != '1'))
		{
			ft_clean_map(data);
			ft_printf("The map is not surrounded by walls.\n");
			exit (EXIT_FAILURE);
		}
	}
}

void	check_counts(t_data *data, int height, int width)
{
	if (data->map[height][width] != '1' &&
		data->map[height][width] != '0' &&
		data->map[height][width] != 'P' &&
		data->map[height][width] != 'E' &&
		data->map[height][width] != 'C' &&
		data->map[height][width] != '\n')
	{
		ft_printf("There are different map caracteres.\n");
		ft_clean_map(data);
		exit (EXIT_FAILURE);
	}
	if (data->map[height][width] == 'C')
		data->collectible_count++;
	if (data->map[height][width] == 'P')
		data->player_count++;
	if (data->map[height][width] == 'E')
		data->exit_count++;
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
		ft_clean_map(data);
		ft_printf("You need 1 player, 1 exit and at least 1 collectible.\n");
		exit (EXIT_FAILURE);
	}
}

void	check_elements(t_data *data)
{
	create_dup_map(data);
	valid_character(data);
	is_map_surrounded_by_walls(data);
	check_path(data, data->player_x, data->player_y);
	if (data->exit_count != 0 || data->collectible_count != 0)
	{
		ft_printf("Player blocked.\n");
		ft_clean_map(data);
		exit (EXIT_FAILURE);
	}
}
