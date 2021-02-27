/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_flat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:06:15 by mhogg             #+#    #+#             */
/*   Updated: 2021/02/27 13:22:01 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mlx.h>

#define img_width 640
#define img_height 480
#define map_width 24
#define map_height 24

typedef struct  s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}               t_data;

typedef	struct	s_var
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;

}				t_var;

typedef struct	s_all
{
	t_data		*data;
	t_var		*var;
	
	
}				t_all;

void	ft_mlx(t_all all);

int		close_func(void)
{
	exit(0);
}

// int		key_hook(int key)
// {
// 	if (key == 53)
// 		exit(0);
// 	return (0);
// }

void	my_mlx_pixel_put(t_all all, int x, int y, int color)
{
    char    *dst;

    dst = all.data->addr + (y * all.data->line_length + x * (all.data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

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

void		ft_mlx(t_all all)
{
	double deltaDistX;
	double deltaDistY;
	int x = 0;

	while (x < img_width)
    {
 		//calculate ray position and direction
 		double cameraX = 2 * x / (double)img_width - 1; //x-coordinate in camera space
 		double rayDirX = all.var->dir_x + all.var->plane_x * cameraX;
 		double rayDirY = all.var->dir_y + all.var->plane_y * cameraX;
 		//which box of the map we're in
 		int mapX = (int)all.var->pos_x;
 		int mapY = (int)all.var->pos_y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

       //length of ray from one x or y-side to next x or y-side
		deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));

		double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (all.var->pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - all.var->pos_x) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (all.var->pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - all.var->pos_y) * deltaDistY;
		}
	//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if(map[mapX][mapY] > 0)			// запомните твари 
				hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(side == 0)
			perpWallDist = (mapX - all.var->pos_x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - all.var->pos_y + (1 - stepY) / 2) / rayDirY;

      //Calculate height of line to draw on screen
		int lineHeight = (int)(img_height / perpWallDist);
		
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + img_height / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + img_height / 2;
		if(drawEnd >= img_height)
			drawEnd = img_height - 1;
		int y = 0;
		
		// float moveSpeed = 0.3;
		
		// 		while (y < img_height)
		// 		{
		// 			if (y >= drawStart && y <= drawEnd)
		// 				my_mlx_pixel_put(all, x, y, 0xFFFFFF);
		// 			y++;
		// 		}

		//coloring walls
		while (y < img_height)
		{
			if (y >= drawStart && y <= drawEnd)
			{
				if (side == 0)				// S N
				{
					if (all.var->dir_x > 0)
						my_mlx_pixel_put(all, x, y, 0xFF0000);
					else if (all.var->dir_x < 0)
						my_mlx_pixel_put(all, x, y, 0x00FF00);
				}
				if (side == 1)				// W E
				{
					if (all.var->dir_y > 0)
						my_mlx_pixel_put(all, x, y, 0x0000FF);
					else if (all.var->dir_y < 0)
						my_mlx_pixel_put(all, x, y, 0xFFFFFF);
				}
			}
			y++;
		}
		x++;
	}	
}

int		key_hook(int keycode, t_all *all)
{
	float moveSpeed = 0.3;
	if (keycode == 53)
		exit(0);
	mlx_destroy_image(all->data->mlx_ptr, all->data->img);
	if (keycode == 13)
	{
		if(map[(int)(all->var->pos_x + all->var->dir_x * moveSpeed)][(int)(all->var->pos_y)] == 0)
			all->var->pos_x += all->var->dir_x * moveSpeed;
		if(map[(int)(all->var->pos_x)][(int)(all->var->pos_y + all->var->dir_y * moveSpeed)] == 0)
			all->var->pos_y += all->var->dir_y * moveSpeed;
	}
	if (keycode == 2)
	{
		if(map[(int)(all->var->pos_x - all->var->dir_x * moveSpeed)][(int)(all->var->pos_y)] == 0)
			all->var->pos_x -= all->var->dir_x * moveSpeed;
		if(map[(int)(all->var->pos_x)][(int)(all->var->pos_y - all->var->dir_y * moveSpeed)] == 0)
			all->var->pos_y -= all->var->dir_y * moveSpeed;
	}

	if (keycode == 1)
	{
		if(map[(int)(all->var->pos_x + all->var->dir_y * moveSpeed)][(int)(all->var->pos_y)] == 0)
			all->var->pos_x += all->var->dir_y * moveSpeed;
		if(map[(int)(all->var->pos_x)][(int)(all->var->pos_y - all->var->dir_x * moveSpeed)] == 0)
			all->var->pos_y -= all->var->dir_x * moveSpeed;
	}
	if (keycode == 0)
	{
		if(map[(int)(all->var->pos_x - all->var->dir_y * moveSpeed)][(int)(all->var->pos_y)] == 0)
			all->var->pos_x -= all->var->dir_y * moveSpeed;
		if(map[(int)(all->var->pos_x)][(int)(all->var->pos_y + all->var->dir_x * moveSpeed)] == 0)
			all->var->pos_y += all->var->dir_x * moveSpeed;
	}
	all->data->img = mlx_new_image(all->data->mlx_ptr, img_width, img_height);
	all->data->addr = mlx_get_data_addr(all->data->img, &all->data->bits_per_pixel, &all->data->line_length, &all->data->endian);
	ft_mlx(*all);
	mlx_put_image_to_window(all->data->mlx_ptr, all->data->win_ptr, all->data->img, 0, 0);
	return (0);
}

int			main(void)
{
	t_data	data;
	t_var	var;
	t_all	all;
	
	all.data = &data;
	all.var = &var;
	all.var->pos_x = 22;
	all.var->pos_y = 12;
	all.var->dir_x = -1;
	all.var->dir_y = -1;
	all.var->plane_x = 0;
	all.var->plane_y = 0.66;
	
	all.data->mlx_ptr = mlx_init();
	all.data->win_ptr = mlx_new_window(all.data->mlx_ptr, img_width, img_height, "cub3D");
	all.data->img = mlx_new_image(all.data->mlx_ptr, img_width, img_height);
	all.data->addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	ft_mlx(all);
	mlx_put_image_to_window(all.data->mlx_ptr, all.data->win_ptr, all.data->img, 0, 0);
	mlx_hook(all.data->win_ptr, 2, (1L << 0), key_hook, &all);
	//mlx_key_hook(all.data->win_ptr, key_hook, &all); 
	mlx_hook(all.data->win_ptr, 17, 1L<<0, close_func, 0); //exit on close window
	write(1, "open\n", 5);
	mlx_loop(all.data->mlx_ptr);
}
