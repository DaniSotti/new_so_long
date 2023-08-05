#include "mlx_linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "so_long.h"
#include "get_next_line/get_next_line.h"

# define MAP_WIDTH 13
# define MAP_HEIGHT 5
# define TILE_SIZE 64
# define WINDOW_WIDTH (MAP_WIDTH * TILE_SIZE)
# define WINDOW_HEIGHT (MAP_HEIGHT * TILE_SIZE)
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
    char map[MAP_HEIGHT][MAP_WIDTH];
    int player_x;
    int player_y;
    int all_collectibles_collected;
} t_data;

void draw_player(t_data *data)
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
    while (i < MAP_HEIGHT)
    {
        j = 0;
        while (j < MAP_WIDTH)
        {
            int x = j * TILE_SIZE;
            int y = i * TILE_SIZE;

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
    while (i < MAP_HEIGHT)
    {
        j = 0;
        while(j < MAP_WIDTH)
        {
            if (data->map[i][j] == 'C')
                count_algae++;
            j++;
        }
        i++;
    }
     data->all_collectibles_collected = (count_algae == 0 ? 1 : 0);
    return count_algae;
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
    if (data->map[next_y][next_x] != '1')
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

        // Draw the map (without the player)
        //draw_map(data);

        // Draw the player at the new position
        draw_player(data);
    }
     // Check if the player has won the game
    if (data->map[next_y][next_x] == 'E')
    {
        if (!data->all_collectibles_collected)
            return (0);
         data->map[data->player_y][data->player_x] = '0'; // Clear the player's current position
        data->player_x = next_x; // Update the player's position
        data->player_y = next_y;
        draw_map(data); // Redraw the map with the player in the new position
        mlx_destroy_window(data->mlx, data->win); // Close the window after moving to the "Exit"
        exit(0);
        // data->map[data->player_y][data->player_x] = '0'; // Clear the player's current position
        // data->player_x = next_x; // Update the player's position
        // data->player_y = next_y;
        // draw_map(data); // Redraw the map with the player in the new position
        // mlx_destroy_window(data->mlx, data->win); // Close the window after moving to the "Exit"
        // exit(0);
    }
    return 0;
}


int main()
{
    t_data data;
    data.player_x = 0;
    data.player_y = 0;

    int fd = open("maps/test.ber", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening the map file");
        return (1);
    }
    int i = 0;
    char *line;
    while ((line = get_next_line(fd)) && i < MAP_HEIGHT)
    {
         int j;
         j = 0;
         while (j < MAP_WIDTH)
         {
             data.map[i][j] = line[j];
             if (line[j] == 'P')
             {
                 data.player_x = j;
                 data.player_y = i;
             }
             j++;
         }
         free(line);
         i++;
    }
    close (fd);
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, "Map Display");

    draw_map(&data);
    // Register the handle_keypress function as the keyboard event handler
    mlx_hook(data.win, 2, 1L << 0, handle_keypress, &data);
    mlx_loop(data.mlx);

    return 0;
} 
