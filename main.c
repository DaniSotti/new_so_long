#include "mlx_linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "so_long.h"
#include "libft/incs/libft.h"
// #include "get_next_line/get_next_line.h"

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
    int fd;
    char	*map_path;
    int		moves;
} t_data;

void    draw_player(t_data *data)
{
    int img_width;
    int img_height;
	void *tardigrade;

    // Draw the player image at the current player position
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
                    alga = mlx_xpm_file_to_image(data->mlx, "./images/algae.xpm", &img_width, &img_height);
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
    return count_algae;
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

int is_collectible_blocked(char **map, int x, int y, int map_width, int map_height) {
    return (x > 0 && map[y][x - 1] == '1') &&
           (x < map_width - 1 && map[y][x + 1] == '1') &&
           (y > 0 && map[y - 1][x] == '1') &&
           (y < map_height - 1 && map[y + 1][x] == '1');
}

int is_valid_position(int x, int y, int map_width, int map_height) {
    return x >= 0 && x < map_width && y >= 0 && y < map_height;
}

int is_wall(char **map, int x, int y) {
    return map[y][x] == '1';
}

int is_map_surrounded_by_walls(char **map, int map_width, int map_height) {
    for (int i = 0; i < map_height; i++) {
        if (!is_wall(map, 0, i) || !is_wall(map, map_width - 1, i)) {
            return 0; // Left or right edge is not surrounded
        }
    }

    for (int j = 0; j < map_width; j++) {
        if (!is_wall(map, j, 0) || !is_wall(map, j, map_height - 1)) {
            return 0; // Top or bottom edge is not surrounded
        }
    }

    return 1;
}

int check_elements(char **map, int map_width, int map_height) {
    int player_count = 0;
    int exit_count = 0;
    int collectible_count = 0;
    int expected_line_length = map_width;

    int i = 0;
    while (i < map_height) {
        int line_length = ft_strlen(map[i]);

        if (line_length != expected_line_length) {
            ft_printf("Line %d has an incorrect length. Expected: %d, Found: %d.\n", i + 1, expected_line_length, line_length);
            return 0;
        }

        int j = 0;
        while (j < map_width) {
            char cell = map[i][j];
            if (cell != 'P' && cell != '1' && cell != 'C' && cell != 'E' && cell != '0' && cell != '\n')
            {
                ft_printf("There are different map caracteres.\n");
                return 0;
            }
            if (cell == 'P') {
                player_count++;
            } else if (cell == 'E') {
                exit_count++;
            } else if (cell == 'C') {
                collectible_count++;

                // Check for collectibles blocked by walls
                if (is_collectible_blocked(map, j, i, map_width, map_height)) {
                    ft_printf("Collectible at (%d, %d) is completely blocked by walls.\n", i, j);
                    return 0;
                }
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

    if (!is_map_surrounded_by_walls(map, map_width, map_height)) {
        ft_printf("The map is not surrounded by walls.\n");
        return 0;
    }

    return 1;
}

void check_map(t_data *data)
{
    char *line;
    data->map_width = 0;
    data->map_height = 0;
    int line_length = 0; // Inicializar o comprimento da linha

    // Ler o tamanho do mapa
    while ((line = get_next_line(data->fd))) {
         // Calcular o comprimento da linha até o caractere '\n'
        while (line[line_length] != '\0' && line[line_length] != '\n') {
            line_length++;
        }
        if (line[line_length] == '\n') //por algum motivo a quebra de linha e contada
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
    
    // Alocar espaço para as linhas do mapa
    int i = 0;
    while (i < data->map_height) {
        data->map[i] = (char *)malloc(data->map_width * sizeof(char));
        i++;
    }

    data->fd = open(data->map_path, O_RDONLY);
    i = 0;
    while ((line = get_next_line(data->fd))) {
         int line_length = 0; // Inicializar o comprimento da linha

        // Calcular o comprimento da linha até o caractere '\n'
        while (line[line_length] != '\0' && line[line_length] != '\n') {
            line_length++;
        }

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
//Find initial player position
    int i;

    i = 0;
    while (i < data->map_height) {
        int j = 0;
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

int main(int argc, char **argv)
{
    t_data data;
    data.player_x = 0;
    data.player_y = 0;
    data.moves = 1;

    if (argc != 2)
    {
        ft_printf("you need to choose the map name \n");
        return (1);
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

    if (!check_elements(data.map, data.map_width, data.map_height)) {
        // fprintf(stderr, "Invalid map.\n");
        // Liberar memória alocada para o mapa e sair do programa
        // ...
        return 1;
    }
    
    player_initial_position(&data);

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, data.map_width * TILE_SIZE, data.map_height * TILE_SIZE, "So Long");
    
    // Register the handle_keypress function as the keyboard event handler
    mlx_hook(data.win, 2, 1L << 0, handle_keypress, &data);
	mlx_hook(data.win, 17, 1L << 0, handle_window_close, &data);
	mlx_hook(data.win, 12, 1L << 15, handle_expose, &data);
    mlx_loop(data.mlx);
	draw_map(&data);

    // Liberar memória alocada para o mapa
    int i = 0;
    while (i < data.map_height) {
        free(data.map[i]);
        i++;
    }
    free(data.map);

    return 0;
}