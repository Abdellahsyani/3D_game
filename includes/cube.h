/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:04:01 by asyani            #+#    #+#             */
/*   Updated: 2025/09/02 11:04:13 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
#define CUBE_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../lib_ft/libft.h"
#include "mlx.h"
#include "door.h"
#include <sys/time.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define MAX_WIDTH 800
#define MAX_HEIGHT 600

# define KEY_W 119
# define KEY_A 97
# define KEY_E 101
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364

// Movement speeds
# define MOVE_SPEED 0.005
# define ROT_SPEED 0.001

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_player
{
	char	**map;
	double	playerX;
	double	playerY;
	char	direction;
	int	mapX;
	int	mapY;
	float cameraX;
	float planeX;
	float planeY;
	float raydiX;
	float raydiY;
	double dx;
	double dy;
	double dsidX;
	double dsidY;
	double stepX;
	double stepY;
	double wallp;
	int line_height;
	int	start_draw;
	int	end_draw;
	int side;
	int hit;
	int *p;
	float wallX;
	float dirX;
	float dirY;
	int	texX;
	void	*img_wall;
	int x_door;
	int y_door;
	int idx;
}	t_player;

typedef struct s_game
{
	void	*mlx;
	void	*mlx_window;
	t_data	img;
	t_player *player;
	t_door *door;
	t_door	arr_door[100];
	int	count_door;
	int         keys[65536];
	double last_frame_time;

	//North
	void    *north_img;
	char    *north_addr;
	int     north_width;
	int     north_height;
	int     north_bpp;
	int     north_line_len;
	int     north_endian;
	//South
	void    *south_img;
	char    *south_addr;
	int     south_width;
	int     south_height;
	int     south_bpp;
	int     south_line_len;
	int     south_endian;
	//West
	void    *west_img;
	char    *west_addr;
	int     west_width;
	int     west_height;
	int     west_bpp;
	int     west_line_len;
	int     west_endian;
	//east
	void    *east_img;
	char    *east_addr;
	int     east_width;
	int     east_height;
	int     east_bpp;
	int     east_line_len;
	int     east_endian;
	//door
	void    *door_img;
	char    *door_addr;
	int     door_width;
	int     door_height;
	int     door_bpp;
	int     door_line_len;
	int     door_endian;
}	t_game;

float    *direction(char c);
void    set_plane(t_player *player);
void    calc_step(t_player *player);
void    DDA_algo(t_player *player, t_game *game);
void    wall_calc(t_player *player);
void    prep_calcs(t_player *player, int i);
void    put_pixel(t_data *img, int x, int y, int color);
void    draw_wall_column(t_game *game, t_player *player, int column);
void    run_game(t_player *player, t_game *game);
void    init_player_direction(t_player *player);
void    init_player(t_player *player, t_game *game);
int     game_loop(t_game *game);
void    render_frame(t_game *game);
int     close_window(t_game *game);
char    **create_test_map(void);
int     init_cube(void);
int     key_press(int keycode, t_game *game);
int     key_release(int keycode, t_game *game);
void    rotate_player(t_player *player, float angle);
void    handle_movement(t_game *game);
void	load_textures(t_game *game);
int	find_door_idx(t_game *game, int dx, int dy);

#endif
