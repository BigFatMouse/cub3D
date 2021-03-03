#include "cub.h"

unsigned int	my_mlx_pixel_take(t_data *data, int x, int y)
{
	char			*addr;
	unsigned int	color;
	
	addr = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	color = *(unsigned int*)addr;
	return (color);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void   put_tex(t_data *img, t_data *tex, int x, int y)
{
	int x_count = 0, y_count = 0, color;
	while (y_count < 64)
	{
		x_count = 0;
		while(x_count < 64)
		{
			color = my_mlx_pixel_take(tex, x_count, y_count);
			my_mlx_pixel_put(img, x + x_count, y + y_count, color); 
			x_count++;
	 	}
		y_count++;
	}
}

int main()
{
    void *mlx;
    void *win;
    t_data tex;
	t_data img;
	int imgWidth = 720;
	int imgHeight = 480;
    int texWidth = 64;
    int texHeight = 64;
	int color;
	int x = 0, y = 0, i = 0, j = 0;
	
	
    mlx = mlx_init();
    win = mlx_new_window(mlx, imgWidth, imgHeight, "texture");
	img.img = mlx_new_image(mlx, imgWidth, imgHeight);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian); 
	tex.img = mlx_xpm_file_to_image(mlx, "textures/bluestone.xpm", &texWidth, &texHeight);
	tex.addr = mlx_get_data_addr(tex.img, &tex.bits_per_pixel, &tex.line_length, &tex.endian); 
	
	while (y < imgHeight / texHeight)
	{
		x = 0;
		//j = y * texHeight;
		while(x < imgWidth / texWidth)
		{
			//i = x * texWidth;
			put_tex(&img, &tex, x * 64, y * 64);
		 	x++;
	 	}
		y++;
	}
    mlx_put_image_to_window(mlx, win, img.img, 0, 0);
    mlx_loop(mlx);
}