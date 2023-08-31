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

void render_moves(t_data *data)
{
	char *moves_str;

	moves_str = ft_itoa(data->moves);
	mlx_string_put(data->mlx, data->win, 10, 10, 0xFFFFFF, "Moves:");
    mlx_string_put(data->mlx, data->win, 70, 10, 0xFFFFFF, moves_str);
	mlx_string_put(data->mlx, data->win, 0, data->map_height * TILE_SIZE, 0x000000, "");
    free(moves_str);
	//--------------------------//
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
	draw_image(data, "./images/tardigrade_front.xpm", data->player_x, data->player_y);
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

int	is_valid_move(t_data *data)
{
	return (data->map[data->next_y][data->next_x] != '1' &&
		data->map[data->next_y][data->next_x] != 'E');
}

void	update_moves(t_data *data)
{
	int	prev_mov;

	prev_mov = data->moves;
	data->moves++;
	ft_printf("MOVES: %d\n", prev_mov);
}

void	clear_update_position(t_data *data)
{
	if (data->map[data->next_y][data->next_x] == 'C')
        data->map[data->next_y][data->next_x] = '0';
		draw_image(data, "./images/floor_resized.xpm", data->player_x, data->player_y);
	data->player_x = data->next_x;
	data->player_y = data->next_y;
	if (data->player_direction == KEY_RIGHT)
	{
		draw_image(data, "./images/tardigrade_right.xpm", data->player_x, data->player_y);
	}
	else if (data->player_direction == KEY_LEFT)
		draw_image(data, "./images/tardigrade_left.xpm", data->player_x, data->player_y);
	else
		draw_image(data, "./images/tardigrade_front.xpm", data->player_x, data->player_y);
	data->player_direction = 0;
}

int	handle_keypress(int keycode, t_data *data)
{
    data->next_x = data->player_x;
    data->next_y = data->player_y;

	if (keycode == KEY_ESC)
		exit_game(data);
	calculate_next_position(keycode, data);
	render_moves(data);
    if (is_valid_move(data))
    {
        update_moves(data);
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
    return 0;
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
		if (!is_wall(data->map, 0, i) || !is_wall(data->map, data->map_width - 1, i))
			return (0);
		i++;
	}
	j = 0;
	while (j < data->map_width)
	{
		if (!is_wall(data->map, j, 0) || !is_wall(data->map, j, data->map_height - 1))
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
	while (i < data->map_height) {
        line_length = ft_strlen(data->map[i]);

        if (line_length != expected_line_length) {
            ft_printf("Line %d has an incorrect length. Expected: %d, Found: %d.\n", i + 1, expected_line_length, line_length);
            return (1);
        }
		i++;
	}
	return (0);
}

void	check_diff_caracteres(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
        while (j < data->map_width)
		{
            if (data->map[i][j] != 'P' && data->map[i][j] != '1' && data->map[i][j] != 'C' && data->map[i][j] != 'E' && data->map[i][j] != '0' && data->map[i][j] != '\n')
            {
                ft_printf("There are different map caracteres.\n");
                exit (1);
            }
			j++;
		}
		i++;
	}
}

int	check_elements(t_data *data)
{
	int	player_count;
    int	exit_count;
    int	collectible_count;
	int	i;
	int j;

	player_count = 0;
	exit_count = 0;
	collectible_count = 0;
    i = 0;
	check_line_length(data);
	check_diff_caracteres(data);
    while (i < data->map_height)
	{
		j = 0;
        while (j < data->map_width)
		{
            if (data->map[i][j] == 'P')
                player_count++;
            else if (data->map[i][j] == 'E')
                exit_count++;
            else if (data->map[i][j] == 'C')
                collectible_count++;
            j++;
        }
        i++;
    }

    if (player_count != 1 || exit_count != 1 || collectible_count == 0) {
        ft_printf("Something wrong.\n");
        return 0;
    }
    if (!is_map_surrounded_by_walls(data)) {
        ft_printf("The map is not surrounded by walls.\n");
        return 0;
    }

    return 1;
}

void	check_map(t_data *data)
{
	char	*line;
	int		line_length;

	line_length = 0;
	data->map_width = 0;
	data->map_height = 0;
	while ((line = get_next_line(data->fd))) 
	{
		while (line[line_length] != '\0' && line[line_length] != '\n')
			line_length++;
        if (line[line_length] == '\n')
            line_length--;
        if (data->map_width > 0 && line_length != data->map_width) {
            ft_printf("Line %d has an incorrect length. Expected: %d, Found: %d.\n", data->map_height + 1,data->map_width, line_length);
            exit(1);
        }
        data->map_width = line_length;
        data->map_height++;
        free(line);
    }
}

void create_map(t_data *data)
{
    char *line;
    data->map = (char **)malloc(data->map_height * sizeof(char *));
    
    int i = 0;
    while (i < data->map_height)
        data->map[i++] = (char *)malloc(data->map_width * sizeof(char));
    data->fd = open(data->map_path, O_RDONLY);
    i = 0;
    while ((line = get_next_line(data->fd))) {
        int line_length = 0;
        while (line[line_length] != '\0' && line[line_length] != '\n')
            line_length++;
        int j = 0;
        while (j < data->map_width) {
            if (j < line_length) {
                data->map[i][j] = line[j];
            } else {
                fprintf(stderr, "The map error.\n");
                exit(1);
            }
            j++;
        }
        data->map[i][j] = '\0'; // Adicionar o caractere nulo no final da linha
        free(line);
        i++;
    }
    close(data->fd);
}

void player_initial_position(t_data *data)
{
    int i;
    int j;

    i = 0;
    while (i < data->map_height) {
        j = 0;
        while (j < data->map_width) {
            if (data->map[i][j] == 'P') {
                data->player_x = j;
                data->player_y = i;
                break;
            }
            j++;
        }
        i++;
    }
}

int handle_window_close(t_data *data)
{
    // Clean up resources and exit the program
    ft_printf("Ohhh! You gave up :(\n");
    free(data->map);
    exit(0);
    return 0;
}

int handle_expose(t_data *data)
{
    draw_map(data);
    return 0;
}

void	ft_clean_map(t_data *data)
{
	int i;

	i = 0;
    while (i < data->map_height) {
		free(data->map[i]);
		i++;
	}
	free(data->map);
}

// Função que verifica se o jogador pode alcançar todos os colecionáveis e a saída
int can_reach_collectibles_and_exit(t_data *data, int start_x, int start_y)
{
    // Define a fila de posições a serem verificadas
    int queue_size = data->map_width * data->map_height;
    int front = 0, rear = 0;
    int queue[queue_size][2];
    int visited[data->map_height][data->map_width];

    // Inicializa a matriz de visitados com zeros
    ft_memset(visited, 0, sizeof(visited));

    // Adiciona a posição inicial do jogador à fila
    queue[rear][0] = start_x;
    queue[rear][1] = start_y;
    rear++;

    // Marca a posição inicial como visitada
    visited[start_y][start_x] = 1;

    // Define as coordenadas de movimento (cima, baixo, esquerda, direita)
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    // Enquanto a fila não estiver vazia
    while (front < rear)
    {
        // Retira a posição da frente da fila
        int current_x = queue[front][0];
        int current_y = queue[front][1];
        front++;

        // Verifica se a posição atual contém um coletável ('C') ou saída ('E')
        if (data->map[current_y][current_x] == 'C' || data->map[current_y][current_x] == 'E')
        {
            // Marca a posição como visitada
            visited[current_y][current_x] = 1;
        }

        // Verifica posições adjacentes
        for (int i = 0; i < 4; i++)
        {
            int new_x = current_x + dx[i];
            int new_y = current_y + dy[i];

            // Verifica se a nova posição é válida e não é uma parede ('1')
            if (new_x >= 0 && new_x < data->map_width &&
                new_y >= 0 && new_y < data->map_height &&
                data->map[new_y][new_x] != '1' &&
                !visited[new_y][new_x])
            {
                // Adiciona a nova posição à fila
                queue[rear][0] = new_x;
                queue[rear][1] = new_y;
                rear++;

                // Marca a posição como visitada
                visited[new_y][new_x] = 1;
            }
        }
    }

    // Verifica se todos os colecionáveis e a saída foram visitados
    for (int i = 0; i < data->map_height; i++)
    {
        for (int j = 0; j < data->map_width; j++)
        {
            if ((data->map[i][j] == 'C' || data->map[i][j] == 'E') && !visited[i][j])
            {
                return 0; // Não é possível alcançar todos os colecionáveis e a saída
            }
        }
    }

    return 1; // O jogador pode alcançar todos os colecionáveis e a saída
}

int main(int argc, char **argv)
{
	t_data	data;

	data.player_x = 0;
	data.player_y = 0;
	data.moves = 1;
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
	if (!check_elements(&data))
        return (1);
	player_initial_position(&data);
	if (!can_reach_collectibles_and_exit(&data, data.player_x, data.player_y))
    {
        ft_printf("O jogador não pode alcançar todos os colecionáveis e/ou a saída.\n");
        ft_clean_map(&data);
        return 1;
    }
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.map_width * TILE_SIZE,
			data.map_height * TILE_SIZE, "So Long");
	mlx_hook(data.win, 2, 1L << 0, handle_keypress, &data);
	mlx_hook(data.win, 17, 1L << 0, handle_window_close, &data);
	mlx_hook(data.win, 12, 1L << 15, handle_expose, &data);
	mlx_loop(data.mlx);
	draw_map(&data);
	ft_clean_map(&data);
	return (0);
}
