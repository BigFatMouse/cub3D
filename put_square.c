/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:44:01 by mhogg             #+#    #+#             */
/*   Updated: 2021/02/26 00:52:49 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define map_width 24
#define map_height 24

typedef struct  s_img
{
	void		*mlx_ptr;
	void		*win_ptr;
    void        *img_ptr;
    char		*img_data;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_img;

typedef struct  s_var 
{
	int			sq_size;
	int			img_width;
	int			img_height;
}				t_var;

typedef struct  s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_global
{
	t_img		*image;
	t_var		*var;
	t_color		*color;
}				t_global;

int map[map_width][map_height]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int		key_hook(int key)
{
	if (key == 53)
		exit(0);
	return (0);
}

int		close_func(t_img image)
{
	// mlx_destroy_image(image.mlx_ptr, image.img_ptr);
	// mlx_destroy_window(image.mlx_ptr, image.img_ptr);
	exit(0);
}

void	my_mlx_pixel_put(t_img *image, int x, int y, int color)
{
    char    *dst;

    dst = image->img_data + (y * image->line_length + x * (image->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

float	grad_to_radian(int grad)
{
	return (M_PI * grad / 180);
}

void	put_square(t_img *image, t_var *var, int x, int y, int color)
{
	int	x_count;
	int	y_count;
	
	y_count = 0;
	
	while (y_count < var->sq_size)
	{
		x_count = 0;
		while(x_count < var->sq_size)
		{
				my_mlx_pixel_put(image, x_count + x, y_count + y, color); 
			x_count++;
	 	}
		y_count++;
	}
}

void	put_map(t_img *image, t_var *var, int color)
{
	int	i;
	int	j;
	
	j = 0;
	i = 0;
	
	while (j < map_height)
	{
		i = 0;
		while (i < map_width)
		{
			if (map[i][j] == 1 || map[i][j] == 2 || map[i][j] == 3 || map[i][j] == 4 || map[i][j] == 5)
				put_square(image, var, i * var->sq_size, j * var->sq_size, color);
				//my_mlx_pixel_put(image, i, j, color);
			i++;
		}
		j++;
	}
}

int		main(void)
{
	int			x;
	int			y;
	float		angle;
	t_var		var;
	t_img		image;
	t_global	global;
	
	var.sq_size = 20;
	var.img_width = 640;
	var.img_height = 480;
	
	x = 100;
	y = 20;
	angle = 30;
	int r = 255;
	int g = 255;
	int b = 255;
	
	int color = create_trgb(0, r, g, b);

	image.mlx_ptr = mlx_init(); // Initializes the mlx library. Will return NULL if initialization failed.
	image.win_ptr = mlx_new_window(image.mlx_ptr, var.img_width, var.img_height, "cub3D"); 
	image.img_ptr = mlx_new_image(image.mlx_ptr, var.img_width, var.img_height);
	image.img_data = mlx_get_data_addr(image.img_ptr, &image.bits_per_pixel, &image.line_length,
                                 &image.endian); 
	
	//put_square(&image, &var, x, y, color);
	put_map(&image, &var, color);
	
	mlx_put_image_to_window(image.mlx_ptr, image.win_ptr, image.img_ptr, 0, 0);
	mlx_key_hook(image.win_ptr, key_hook, 0); // exit on ESC
	mlx_hook(image.win_ptr, 17, 1L<<0, close_func, 0); // exit when window is closed 
	mlx_loop(image.mlx_ptr); 
	return (0);
}
