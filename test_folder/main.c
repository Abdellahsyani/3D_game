#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int draw_pixel(char *data, int x, int y, int color, int size_line, int bpp)
{
    int offset = y * size_line + x * (bpp / 8);
    data[offset + 0] = color & 0xFF;
    data[offset + 1] = (color >> 8) & 0xFF;
    data[offset + 2] = (color >> 16) & 0xFF;
    return 0;
}

// DDA algo
void draw_line(char *data, int x0, int y0, int x1, int y1, int color, int size_line, int bpp)
{
	float dx = x1 - x0;
	float dy = y1 - y0;
	float steps = 0;
	float step_x = 0;
	float step_y = 0;

	if (fabs(dx) > fabs(dy))
		steps = dx;
	else
		steps = dy;
	step_x = dx / steps;
	step_y = dy / steps;
	float x = x0;
	float y = y0;

	for (int i = 0; i <= steps; i++)
	{
		draw_pixel(data, (int)x, (int)y, color, size_line, bpp);
		x += step_x;
		y += step_y;
	}
}

void draw_rectangle(char *data, int start_x, int start_y, int width, int height, int color, int size_line, int bpp)
{
	int i = -90;
	int x1 = 90, y1 = 200;
	int dis = 110;
	int theta = 60;
	while (theta <= 380)
	{
		float theta_rad = theta * M_PI / 180.0;
		float n_x = sin(theta_rad) * dis + 90;
		float n_y = cos(theta_rad) * dis + 90;
		draw_line(data, 90, 90, (int)n_x, (int)n_y, color, size_line, bpp);
		theta += 2;
	}
}

int main()
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1000, 1600, "cube3d");
	img.img = mlx_new_image(mlx, 800, 700);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_rectangle(img.addr, 100, 100, 50, 30, 0x00FF0000, img.line_length, img.bits_per_pixel);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 50, 10);

	mlx_loop(mlx);

	return (0);
}
