/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:04:01 by asyani            #+#    #+#             */
/*   Updated: 2025/11/22 18:21:59 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIN_WIDTH 1800
# define WIN_HEIGHT 1200
# define MAX_WIDTH 800
# define MAX_HEIGHT 600

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.01

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct s_player
{
	char			**map;
	double			player_x;
	double			player_y;
	char			direction;
	int				map_x;
	int				map_y;
	float			camera_x;
	float			plane_x;
	float			plane_y;
	float			raydi_x;
	float			raydi_y;
	double			dx;
	double			dy;
	double			dsid_x;
	double			dsid_y;
	double			step_x;
	double			step_y;
	double			wallp;
	int				line_height;
	int				start_draw;
	int				end_draw;
	int				side;
	int				hit;
	int				*p;
	float			wall_x;
	float			dir_x;
	float			dir_y;
	int				tex_x;
	void			*img_wall;
	int				roof[3];
	int				floor[3];
	char			*northimg;
	char			*southimg;
	char			*westimg;
	char			*eastimg;
	// variable for draw W S
	float			step;
	float			tex_pos;
	int				tex_height;
	int				tex_width;
	unsigned char	*tex_addr;
	int				bpp;
	int				line_len;
}					t_player;

typedef struct s_game
{
	void			*mlx;
	void			*mlx_window;
	t_data			img;
	t_player		*player;
	int				keys[65536];

	// North
	void			*north_img;
	char			*north_addr;
	int				north_width;
	int				north_height;
	int				north_bpp;
	int				north_line_len;
	int				north_endian;
	// South
	void			*south_img;
	char			*south_addr;
	int				south_width;
	int				south_height;
	int				south_bpp;
	int				south_line_len;
	int				south_endian;
	// West
	void			*west_img;
	char			*west_addr;
	int				west_width;
	int				west_height;
	int				west_bpp;
	int				west_line_len;
	int				west_endian;
	// east
	void			*east_img;
	char			*east_addr;
	int				east_width;
	int				east_height;
	int				east_bpp;
	int				east_line_len;
	int				east_endian;
}					t_game;

float				*direction(char c);
void				set_plane(t_player *player);
void				calc_step(t_player *player);
void				dda_algo(t_player *player);
void				wall_calc(t_player *player);
void				prep_calcs(t_player *player, int i);
void				put_pixel(t_data *img, int x, int y, int color);
void				draw_wall_column(t_game *game, t_player *player,
						int column);
void				run_game(t_player *player, t_game *game);
void				init_player_direction(t_player *player);
void				init_player(t_player *player);
int					game_loop(t_game *game);
void				render_frame(t_game *game);
int					close_window(t_game *game);
char				**create_test_map(void);
int					init_cube(t_player *player);
int					key_press(int keycode, t_game *game);
int					key_release(int keycode, t_game *game);
void				rotate_player(t_player *player, float angle);
void				handle_movement(t_game *game);
void				load_textures(t_game *game);
int					pars_fun(int argc, char **argv, t_player *player);
void				draw_wall(t_game *game, t_player *player, int column);

//-----------------------------utils-------------------------

int					safe_char_at(char **map, int i, int j, char flag);
int					check_zero(char **str, int i, int j);
void				free_all(t_game *game);
void				error_exit(char *msg, t_game *game);
char				*read_line(char *s);
int					ft_whitespace(int c);
int					ft_identif(int c);
int					iswhitespace(char *s);
int					is_valid(int c);
int					ft_side(char *s);
int					find_one(char **map);
int					ft_direction(char c, t_player *player, int i, int j);
int					check_spaces(char **map, int i, int j);
int					check_map(char *s);
void				skip_spaces(char *str, int *i);
int					ft_valid_id(char *str, t_player *player);
int					open_file(char *s);
int					check_inside_map(char *str);
int					check_range(char *s, t_player *player);
int					path_checker(char *s, t_player *player);
int					check_in_map(char **map, t_player *player);
void				ft_free(char **arr);
void				fill_map(char **str, t_player *player);
void				ft_free_path(t_player *player);
int					get_only_map(char **str, int *i);

#endif
