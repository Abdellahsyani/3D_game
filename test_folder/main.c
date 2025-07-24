#include <mlx.h>
#include <stdio.h>

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

void draw_rectangle(char *data, int start_x, int start_y, int width, int height, int color, int size_line, int bpp)
{
        for (int x = 0; x < width; x++)
	{
            draw_pixel(data, x, 0, color, size_line, bpp);
            draw_pixel(data, x, height - 1, color, size_line, bpp);
	}
        for (int y = 0; y < height; y++)
	{
            draw_pixel(data, 0, y, color, size_line, bpp);
            draw_pixel(data, width - 1, y, color, size_line, bpp);
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
	draw_rectangle(img.addr, 100, 100, 50, 30, 0x00FF00, img.line_length, img.bits_per_pixel);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 50, 10);

	mlx_loop(mlx);

	return (0);
}
