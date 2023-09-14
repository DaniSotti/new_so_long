#include "mlx_linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "so_long.h"
#include "libft/incs/libft.h"


# define TILE_SIZE 64
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_W 119
# define KEY_ESC 65307
# define PLAYER "./images/tardigrade.xpm"

typedef struct s_data {
    void *mlx;
    void *win;
    char **map;
    int player_x;
    int player_y;
    // int all_collectibles_collected;
    int map_width;
    int map_height;
    int win_width;
    int win_height;
    int fd;
    char	*map_path;
    int		moves;
} t_data;

// Initialize data structure
void initialize_data(t_data *data, const char *map_name)
{
	// ft_bzero(data, sizeof(t_data)); // Initialize all fields to 0
	// data->moves = 1;
	data->map_path = ft_strjoin(ft_strjoin("maps/", map_name), ".ber");
	data->fd = open(data->map_path, O_RDONLY);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->map_width * TILE_SIZE,
			data->map_height * TILE_SIZE, "So Long"); // Window size will be set later
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

int is_wall(char **map, int x, int y) {
    return map[y][x] == '1';
}

int is_map_surrounded_by_walls(t_data *data) {
	int	i;
	int j;

	i = 0;
	while (i < data->map_height)
	{
		if (!is_wall(data->map, 0, i) || !is_wall(data->map, data->map_width - 1, i)) {
            return 0; // Left or right edge is not surrounded
        }
		i++;
	}
	j = 0;
	while (j < data->map_width)
	{
		if (!is_wall(data->map, j, 0) || !is_wall(data->map, j, data->map_height - 1)) {
            return 0; // Top or bottom edge is not surrounded
        }
		j++;
	}
    return 1;
}

int check_elements(t_data *data) {
    int player_count = 0;
    int exit_count = 0;
    int collectible_count = 0;
    int expected_line_length = data->map_width;

    int i = 0;
    while (i < data->map_height) {
        int line_length = ft_strlen(data->map[i]);

        if (line_length != expected_line_length) {
            ft_printf("Line %d has an incorrect length. Expected: %d, Found: %d.\n", i + 1, expected_line_length, line_length);
            return 0;
        }

        int j = 0;
        while (j < data->map_width) {
            char cell = data->map[i][j];
            if (cell != 'P' && cell != '1' && cell != 'C' && cell != 'E' && cell != '0' && cell != '\n')
            {
                ft_printf("There are different map caracteres.\n");
                return 0;
            }
            if (cell == 'P') {
                player_count++;
            } else if (cell == 'E') {
                exit_count++;
				// if (is_exit_blocked(data, j, i)) {
                //     ft_printf("Exit at (%d, %d) is completely blocked by walls.\n", i, j);
                //     return 0;
                // }
            } else if (cell == 'C') {
                collectible_count++;

                // Check for collectibles blocked by walls
                // if (is_collectible_blocked(data, j, i)) {
                //     ft_printf("Collectible at (%d, %d) is completely blocked by walls.\n", i, j);
                //     return 0;
                // }
            }
            j++;
        }
        i++;
    }
    if (player_count != 1) {
        ft_printf("There should be exactly one player ('P') on the map.\n");
        return 0;
    }

    if (exit_count != 1) {
        ft_printf("There should be exactly one exit ('E') on the map.\n");
        return 0;
    }

    if (collectible_count == 0) {
        ft_printf("There should be at least one collectible ('C') on the map.\n");
        return 0;
    }

    if (!is_map_surrounded_by_walls(data)) {
        ft_printf("The map is not surrounded by walls.\n");
        return 0;
    }

    return 1;
}

// Load and check map
int load_and_check_map(t_data *data)
{
	check_map(data);
	close(data->fd);
	create_map(data);
	return check_elements(data);
}

// Initialize player position
void initialize_player(t_data *data)
{
	int i, j;
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
				return;
			}
			j++;
		}
		i++;
	}
}

// Set up the MLX window
void setup_mlx(t_data *data)
{
	data->win_width = data->map_width * TILE_SIZE;
	data->win_height = data->map_height * TILE_SIZE;
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height, "So Long");
}

void	draw_player(t_data *data)
{
    int		img_width;
    int		img_height;
	void	*tardigrade;
	
	tardigrade = mlx_xpm_file_to_image(data->mlx, PLAYER, &img_width, &img_height);
    mlx_put_image_to_window(data->mlx, data->win, tardigrade, data->player_x * TILE_SIZE, data->player_y * TILE_SIZE);
}

void draw_map(t_data *data)
{
    int i;
	int j;
    int img_width;
	int img_height;
	void *wall;
	void *exit;
	void *alga;
	void *floor;

    i = 0;
    while (i < data->map_height)
    {
        j = 0;
        while (j < data->map_width)
        {
            if (i < data->map_height && j < data->map_width) {
                if (data->map[i][j] == '1')
                {
                    wall = mlx_xpm_file_to_image(data->mlx, "./images/wall.xpm", &img_width, &img_height);
                    mlx_put_image_to_window(data->mlx, data->win, wall, j * TILE_SIZE, i * TILE_SIZE);
                }
                else if (data->map[i][j] == 'E')
                {
                    exit = mlx_xpm_file_to_image(data->mlx, "./images/exit.xpm", &img_width, &img_height);
                    mlx_put_image_to_window(data->mlx, data->win, exit, j * TILE_SIZE, i * TILE_SIZE);
                }
                else if (data->map[i][j] == 'C')
                {
                    alga = mlx_xpm_file_to_image(data->mlx, "./images/algae32.xpm", &img_width, &img_height);
                    mlx_put_image_to_window(data->mlx, data->win, alga, j * TILE_SIZE, i * TILE_SIZE);
                }
                else
                {
                    floor = mlx_xpm_file_to_image(data->mlx, "./images/floor.xpm", &img_width, &img_height);
                    mlx_put_image_to_window(data->mlx, data->win, floor, j * TILE_SIZE, i * TILE_SIZE);
                }
            }
            j++;
        }
        i++;
    }
    draw_player(data);
}

int handle_window_close(t_data *data)
{
    // Clean up resources and exit the program
    ft_printf("Ohhh! You gave up :(\n");
    free(data->map);
    exit(0);
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

// Clean up resources and exit
void clean_up_and_exit(t_data *data)
{
	ft_clean_map(data); // Assuming you have this function
	exit(0);
}



void    draw_new_exit(t_data *data)
{
    int img_width;
	int img_height;
    int i;
	int j;

    i = 0;
    while (i < data->map_height)
    {
        j = 0;
        while (j < data->map_width)
        {
            if (i < data->map_height && j < data->map_width) 
            {
                if (data->map[i][j] == 'E')
                {
                    void *new_exit = mlx_xpm_file_to_image(data->mlx, "./images/algae.xpm", &img_width, &img_height);
                    mlx_put_image_to_window(data->mlx, data->win, new_exit, j * TILE_SIZE, i * TILE_SIZE);
                }
            }
            j++;
        }
        i++;
    }
}

int check_game_state(t_data *data)
{
    int i;
	int j;
    int count_algae;
	
	count_algae = 0;
    i = 0;
    while (i < data->map_height)
    {
        j = 0;
        while(j < data->map_width)
        {
            if (data->map[i][j] == 'C')
                count_algae++;
            j++;
        }
        i++;
    }
    return (count_algae);
}


int handle_keypress(int keycode, t_data *data)
{
    int prev_x = data->player_x;
    int prev_y = data->player_y;
    int next_x = data->player_x;
    int next_y = data->player_y;
    int img_width;
	int img_height;
    int prev_mov;
	void *floor;

    prev_mov = data->moves;
    // Calculate the next position based on the key pressed
    if (keycode == KEY_UP || keycode == KEY_W)
        next_y--;
    else if (keycode == KEY_DOWN || keycode == KEY_S)
        next_y++;
    else if (keycode == KEY_LEFT || keycode == KEY_A)
        next_x--;
    else if (keycode == KEY_RIGHT || keycode == KEY_D)
        next_x++;
	else if (keycode == KEY_ESC)
	{
		ft_printf("Ohhh! You gave up :( \n");
		free (data->map);
		exit (0);
	}
    // Check if the next position is valid (not a wall)
    if (data->map[next_y][next_x] != '1' && data->map[next_y][next_x] != 'E')
    {
        data->moves++;
        ft_printf("MOVES: %d\n", prev_mov);
        // If the next position contains 'C', change it to '0'
        if (data->map[next_y][next_x] == 'C')
            data->map[next_y][next_x] = '0';
        // Clear the player's previous position
        floor = mlx_xpm_file_to_image(data->mlx, "./images/floor.xpm", &img_width, &img_height);
        mlx_put_image_to_window(data->mlx, data->win, floor, prev_x * TILE_SIZE, prev_y * TILE_SIZE);

        // Update the player's position
        data->player_x = next_x;
        data->player_y = next_y;

        // Draw the player at the new position
        draw_player(data);
        if (check_game_state(data) == 0)
            draw_new_exit(data);
    }
     // Check if the player has won the game
    if (check_game_state(data) == 0)
    {
        if (data->map[next_y][next_x] == 'E')
        {
            ft_printf("You win :) \n");
            // mlx_destroy_window(data->mlx, data->win); // Close the window after moving to the "Exit"
            exit(0);
        }
    }
    return 0;
}

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

// Handle expose event
int handle_expose(t_data *data)
{
	draw_map(data);
    return (0);
}

int main(int argc, char **argv)
{
	t_data data;

	if (argc != 2)
	{
		ft_printf("You need to choose the map name.\n");
		return (1);
	}

	initialize_data(&data, argv[1]);

	if (!load_and_check_map(&data))
	{
		ft_printf("Map loading and checking failed.\n");
		clean_up_and_exit(&data);
	}

	initialize_player(&data);

	if (!can_reach_collectibles_and_exit(&data, data.player_x, data.player_y))
	{
		ft_printf("Player cannot reach all collectibles and/or the exit.\n");
		clean_up_and_exit(&data);
	}

	setup_mlx(&data);

	mlx_hook(data.win, 2, 1L << 0, handle_keypress, &data);
	mlx_hook(data.win, 17, 1L << 0, handle_window_close, &data);
	mlx_hook(data.win, 12, 1L << 15, handle_expose, &data);

	mlx_loop(data.mlx);

	clean_up_and_exit(&data);

	return (0);
}





int render_moves(t_data *data)
{
	char *temp;
	char *movies_str;

	temp = ft_itoa(data->moves);
	movies_str = ft_strjoin("MOVIES: ", temp);
	free(temp);
	draw_map(data);
	mlx_put_image_to_window(data->mlx, data->win, "./images/floor_resized.xpm", 0, 0);
    mlx_string_put(data->mlx, data->win, (data->map_width / 2) - \
		(TILE_SIZE / 2), data->map_height - (TILE_SIZE * 0.45), 0xFFFFFF, movies_str);
    free(movies_str);
	return (0);
	//--------------------------//
}





int	check_valid_caracteres(t_data *data)
{
	int	player_count;
	int	exit_count;
	int	collectible_count;
	int	i;
	int	j;

	player_count = 0;
	exit_count = 0;
	collectible_count = 0;
	i = 0;
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
	if (player_count != 1 || exit_count != 1 || collectible_count == 0)
	{
		ft_printf("Something wrong.\n");
		return (1);
	}
	return (0);
}











//  int	can_reach_collectibles_and_exit(t_data *data, int start_x, int start_y)
//  {
//  	int	queue_size;
//  	int	front;
//  	int	rear;
//  	int	visited[data->map_height][data->map_width];
//  	int	current_x;
//  	int current_y;
// 	queue_size = data->map_width * data->map_height;
//  	front = 0;
//  	rear = 0;
//      ft_memset(visited, 0, sizeof(visited));
//  	int	queue[queue_size][2];
//      queue[rear][0] = start_x;
//      queue[rear][1] = start_y;
//      rear++;
//      visited[start_y][start_x] = 1;
//      int dx[] = {0, 0, -1, 1};
//      int dy[] = {-1, 1, 0, 0};
//      while (front < rear)
//      {
//          current_x = queue[front][0];
//          current_y = queue[front][1];
//          front++;
//  		if (data->map[current_y][current_x] == 'C' || data->map[current_y][current_x] == 'E')
//              visited[current_y][current_x] = 1;
//          int i = 0; 
//  		while (i < 4)
//          {
//              int new_x = current_x + dx[i];
//              int new_y = current_y + dy[i];
//             // Verifica se a nova posição é válida e não é uma parede ('1')
//              if (new_x >= 0 && new_x < data->map_width &&
//                  new_y >= 0 && new_y < data->map_height &&
//                  data->map[new_y][new_x] != '1' &&
//                  !visited[new_y][new_x])
//              {
//                  queue[rear][0] = new_x;
//                  queue[rear][1] = new_y;
//                  rear++;
//                  visited[new_y][new_x] = 1;
//              }
//  			i++;
//          }
//      }
//  	int i = 0;
//      while (i < data->map_height)
//      {
//          int j = 0;
//  		while (j < data->map_width)
//          {
//              if ((data->map[i][j] == 'C' || data->map[i][j] == 'E') && !visited[i][j])
//                  return 0;
//  			j++;
//          }
//  		i++;
//      }
//      return (1);
//  }


//  int	can_reach_collectibles_and_exit(t_data *data)
// {
// 	// int	queue_size;
// 	// int	front;
// 	// int	rear;
// 	// int	visited[data->map_height][data->map_width];
// 	// int	current_x;
// 	// int current_y;

// 	// queue_size = data->map_width * data->map_height;
// 	// front = 0;
// 	// rear = 0;
//     // ft_memset(visited, 0, sizeof(visited));
// 	// int	queue[queue_size][2];
//     // queue[rear][0] = start_x;
//     // queue[rear][1] = start_y;
//     // rear++;
//     // visited[start_y][start_x] = 1;
//     // int dx[] = {0, 0, -1, 1};
//     // int dy[] = {-1, 1, 0, 0};
//     // while (front < rear)
//     // {
//     //     current_x = queue[front][0];
//     //     current_y = queue[front][1];
//     //     front++;
// 	// 	if (data->map[current_y][current_x] == 'C' || data->map[current_y][current_x] == 'E')
//     //         visited[current_y][current_x] = 1;
//     //     int i = 0; 
// 	// 	while (i < 4)
//     //     {
//     //         int new_x = current_x + dx[i];
//     //         int new_y = current_y + dy[i];

//     //         // Verifica se a nova posição é válida e não é uma parede ('1')
//     //         if (new_x >= 0 && new_x < data->map_width &&
//     //             new_y >= 0 && new_y < data->map_height &&
//     //             data->map[new_y][new_x] != '1' &&
//     //             !visited[new_y][new_x])
//     //         {
//     //             queue[rear][0] = new_x;
//     //             queue[rear][1] = new_y;
//     //             rear++;
//     //             visited[new_y][new_x] = 1;
//     //         }
// 	// 		i++;
//     //     }
//     // }

//  	int collectible_count;
//  	int exit;
//  	collectible_count = data->collectible_count;
//  	exit = data->exit_count;
//  	int i = 0;
//      while (i < data->map_height)
//      {
//         int j = 0;
//  		while (j < data->map_width)
//          {
//             if (data->map[i][j] == 'C')
//  				collectible_count--;
//  			else if (data->map[i][j] == 'E')
//  				exit--;
// 			data->map[i][j] == 'F';
//  			j++;
//         }
//  		i++;
//      }
//  	if (collectible_count == 0 && exit == 0)
//  		return (1);
//  	else
//      	return (0);
//  }


//  int is_collectible_blocked(t_data *data) {
//  	//Eu vou na posicao pra cima pra baixo e para os lados verificando se tenho 1 e retorno erro caso sim
// 	int x = 0, y = 0;
//     int blocked_collectible_count = 0;

// 	 	while (y < data->map_height) {
//         x = 0;
//         while (x < data->map_width) {
// 			if (data->map[y][x] == 'C') {
// 			  if (x > 0 && data->map[y][x - 1] == '1' &&
//                     x < data->map_width - 1 && data->map[y][x + 1] == '1' &&
//                     y > 0 && data->map[y - 1][x] == '1' &&
//                     y < data->map_height - 1 && data->map[y + 1][x] == '1') {
//                     blocked_collectible_count++;
//                 }
// 			}
// 		}
// 	}
	
//     return blocked_collectible_count;
//  }

// int count_blocked_exits(t_data *data) {
//     int x = 0, y = 0;
//     int blocked_exit_count = 0;

//     while (y < data->map_height) {
//         x = 0;
//         while (x < data->map_width) {
//             if (data->map[y][x] == 'E') {
//                 // Verifica se a saída está bloqueada em todas as direções.
//                 if (x > 0 && data->map[y][x - 1] == '1' &&
//                     x < data->map_width - 1 && data->map[y][x + 1] == '1' &&
//                     y > 0 && data->map[y - 1][x] == '1' &&
//                     y < data->map_height - 1 && data->map[y + 1][x] == '1') {
//                     blocked_exit_count++;
//                 }
//             }
//             x++;
//         }
//         y++;
//     }

//     return blocked_exit_count;
// }

// void check_path(t_data *data, int x, int y);

// void path_mark(t_data *data, int x, int y)
// {
// 	if (x >= 0 && x < data->map_width && y >= 0 && y < data->map_height)
// 	{
// 		// x, y é a posição do meu player
// 		if (data->map[y][x] == 'P')
// 			data->map[y][x] = 'p';
// 		if (data->map[y][x] == 'C')
// 		{
// 			data->map[y][x] = 'c';
// 			data->collectibles++;
// 		}
// 		if (data->map[y][x] == '0')
// 			data->map[y][x] = 'o';
// 		if (data->map[y][x] == 'E')
// 		{
// 			data->map[y][x] = 'e';
// 			data->exit++;
// 		}
// 		else
// 		{
// 			check_path(data, x + 1, y);
// 			check_path(data, x - 1, y);
// 			check_path(data, x, y + 1);
// 			check_path(data, x, y - 1);
// 		}
// 	}
// }

// void check_path(t_data *data, int x, int y)
// {
// 	if (data->map[y][x] == 'P' || data->map[y][x] == 'E' || data->map[y][x] == 'C' || data->map[y][x] == '0')
// 	{
// 		path_mark(data, x, y);
// 	}
// }