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

#include "include/so_long.h"

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

void	init_game(t_data *data, char *map_name)
{
	char	*s;

	data->player_x = 0;
	data->player_y = 0;
	data->moves = 0;
	data->prev_mov_int = 0;
	data->map_width = 0;
	data->map_height = 0;
	data->length = 0;
	s = ft_strjoin("maps/", map_name);
	data->map_path = ft_strjoin(s, ".ber");
	free(s);
	if (data->map_path == NULL)
	{
		ft_printf("Error creating map path.\n");
		exit (EXIT_FAILURE);
	}
	count_size_map(data);
	create_map(data);
	player_initial_position(data);
}

int	main(int argc, char **argv)
{
	static t_data	data;

	if (argc != 2)
	{
		ft_printf("you need to choose the map name.\n");
		return (1);
	}
	init_game(&data, argv[1]);
	check_elements(&data);
	create_window(&data);
	render_moves(&data);
	mlx_hook(data.win, 12, 0, draw_map, &data);
	mlx_hook(data.win, 2, 1L << 0, handle_keypress, &data);
	mlx_hook(data.win, 17, 1L << 0, exit_game, &data);
	mlx_loop(data.mlx);
	ft_clean_map(&data);
	return (0);
}
