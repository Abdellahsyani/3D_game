#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

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

void draw_line(char *data, int x0, int y0, int x1, int y1, int color, int size_line, int bpp)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		draw_pixel(data, x0, y0, color, size_line, bpp);
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void draw_rectangle(char *data, int start_x, int start_y, int width, int height, int color, int size_line, int bpp)
{
	draw_line(data, 10, 10, 100, 10, color, size_line, bpp);
	draw_line(data, 10, 10, 100, 60, color, size_line, bpp);
	draw_line(data, 100, 10, 100, 60, color, size_line, bpp);
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
