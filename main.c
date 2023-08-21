#include "mlx_linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "so_long.h"
#include "get_next_line/get_next_line.h"

# define TILE_SIZE 64
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define PLAYER "./images/tardigrade.xpm"

typedef struct s_data {
    void *mlx;
    void *win;
    void *img_ptr;
    char *data;
    int width;
    int height;
    int bpp;
    int size_line;
    int endian;
    char **map;
    int player_x;
    int player_y;
    int all_collectibles_collected;
    int map_width;
    int map_height;
    int fd;
    char	*map_path;
} t_data;

void    draw_player(t_data *data)
{
    int img_width, img_height;

    // Draw the player image at the current player position
    int player_x = data->player_x * TILE_SIZE;
    int player_y = data->player_y * TILE_SIZE;
    void *tardigrade = mlx_xpm_file_to_image(data->mlx, PLAYER, &img_width, &img_height);
    mlx_put_image_to_window(data->mlx, data->win, tardigrade, player_x, player_y);
}


void draw_map(t_data *data)
{
    int i, j;
    int img_width, img_height;

    i = 0;
    while (i < data->map_height)
    {
        j = 0;
        while (j < data->map_width)
        {
            int x = j * TILE_SIZE;
            int y = i * TILE_SIZE;

            if (i < data->map_height && j < data->map_width) {
                if (data->map[i][j] == '1')
                {
                    void *wall = mlx_xpm_file_to_image(data->mlx, "./images/wall.xpm", &img_width, &img_height);
                    mlx_put_image_to_window(data->mlx, data->win, wall, x, y);
                }
                else if (data->map[i][j] == 'E')
                {
                    void *exit = mlx_xpm_file_to_image(data->mlx, "./images/exit.xpm", &img_width, &img_height);
                    mlx_put_image_to_window(data->mlx, data->win, exit, x, y);
                }
                else if (data->map[i][j] == 'C')
                {
                    void *alga = mlx_xpm_file_to_image(data->mlx, "./images/algae.xpm", &img_width, &img_height);
                    mlx_put_image_to_window(data->mlx, data->win, alga, x, y);
                }
                else
                {
                    void *floor = mlx_xpm_file_to_image(data->mlx, "./images/floor.xpm", &img_width, &img_height);
                    mlx_put_image_to_window(data->mlx, data->win, floor, x, y);
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
    int i, j;
    int count_algae = 0;

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
    //  data->all_collectibles_collected = (count_algae == 0 ? 1 : 0);

    return count_algae;
}

void    draw_new_exit(t_data *data)
{
    int img_width, img_height;
    int i, j;

    i = 0;
    while (i < data->map_height)
    {
        j = 0;
        while (j < data->map_width)
        {
            int player_x = j * TILE_SIZE;
            int player_y = i * TILE_SIZE;

            if (i < data->map_height && j < data->map_width) 
            {
                if (data->map[i][j] == 'E')
                {
                    void *new_exit = mlx_xpm_file_to_image(data->mlx, "./images/algae.xpm", &img_width, &img_height);
                    mlx_put_image_to_window(data->mlx, data->win, new_exit, player_x, player_y);
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
    int img_width, img_height;

    // Calculate the next position based on the key pressed
    if (keycode == KEY_UP)
        next_y--;
    else if (keycode == KEY_DOWN)
        next_y++;
    else if (keycode == KEY_LEFT)
        next_x--;
    else if (keycode == KEY_RIGHT)
        next_x++;

    // Check if the next position is valid (not a wall)
    if (data->map[next_y][next_x] != '1' && data->map[next_y][next_x] != 'E')
    {
        // If the next position contains 'C', change it to '0'
        if (data->map[next_y][next_x] == 'C')
            data->map[next_y][next_x] = '0';
        // Clear the player's previous position
        void *floor = mlx_xpm_file_to_image(data->mlx, "./images/floor.xpm", &img_width, &img_height);
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
            mlx_destroy_window(data->mlx, data->win); // Close the window after moving to the "Exit"
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

int validate_map(char **map, int map_width, int map_height) {
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

int main(int argc, char **argv)
{
    t_data data;
    data.player_x = 0;
    data.player_y = 0;

    if (argc != 2)
    {
        ft_printf("you should choose the map\n");
        return (1);
    }

    data.map_path = argv[1];
    data.fd = open(data.map_path, O_RDONLY);
    if (data.fd == -1)
    {
        perror("Error opening the map file");
        return (1);
    }

    char *line;
    int i = 0;
    data.map_width = 0;
    data.map_height = 0;
    int line_length = 0; // Inicializar o comprimento da linha

    // Ler o tamanho do mapa
    while ((line = get_next_line(data.fd))) {
         // Calcular o comprimento da linha até o caractere '\n'
        while (line[line_length] != '\0' && line[line_length] != '\n') {
            line_length++;
        }
        if (line[line_length] == '\n') //por algum motivo a quebra de linha e contada
            line_length--;
        if (data.map_width > 0 && line_length != data.map_width) {
            fprintf(stderr, "Line %d has an incorrect length. Expected: %d, Found: %d.\n", data.map_height + 1,data.map_width, line_length); //Trocar funcao
        return 1;
        }
        data.map_width = line_length;
        data.map_height++;

        free(line);
    }

    close(data.fd);

    data.map = (char **)malloc(data.map_height * sizeof(char *));
    
    // Alocar espaço para as linhas do mapa
    i = 0;
    while (i < data.map_height) {
        data.map[i] = (char *)malloc(data.map_width * sizeof(char));
        i++;
    }

    data.fd = open(data.map_path, O_RDONLY);
    i = 0;
    while ((line = get_next_line(data.fd))) {
        // int line_length = 0; // Inicializar o comprimento da linha

        // // Calcular o comprimento da linha até o caractere '\n'
        // while (line[line_length] != '\0' && line[line_length] != '\n') {
        //     line_length++;
        // }

        int j = 0;
        while (j < data.map_width) {
            if (j < line_length) {
                data.map[i][j] = line[j];
            } else {
                fprintf(stderr, "The map error.\n");
                return (0);
            }
            j++;
        }
        data.map[i][j] = '\0'; // Adicionar o caractere nulo no final da linha
        free(line);
        i++;
    }
    close(data.fd);

    if (!validate_map(data.map, data.map_width, data.map_height)) {
        // fprintf(stderr, "Invalid map.\n");
        // Liberar memória alocada para o mapa e sair do programa
        // ...
        return 1;
    }

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, data.map_width * TILE_SIZE, data.map_height * TILE_SIZE, "Map Display");

    // Find initial player position
    i = 0;
    while (i < data.map_height) {
        int j = 0;
        while (j < data.map_width) {
            if (data.map[i][j] == 'P') {
                data.player_x = j;
                data.player_y = i;
                break;
            }
            j++;
        }
        i++;
    }

    draw_map(&data);
    // Register the handle_keypress function as the keyboard event handler
    mlx_hook(data.win, 2, 1L << 0, handle_keypress, &data);
    mlx_loop(data.mlx);

    // Liberar memória alocada para o mapa
    i = 0;
    while (i < data.map_height) {
        free(data.map[i]);
        i++;
    }
    free(data.map);

    return 0;
}