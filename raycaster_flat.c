/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_flat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:06:15 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/03 02:10:42 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		close_func(void)
{
	exit(0);
}

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
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int map[map_width][map_height]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void put_texture(t_all *all)
{
	int	x = 0;
	int	y = 0;	
	
}

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
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
		if(rayDirX < 0)
		{
			all.var->step_x = -1;
			sideDistX = (all.var->pos_x - mapX) * deltaDistX;
		}
		else
		{
			all.var->step_x = 1;
			sideDistX = (mapX + 1.0 - all.var->pos_x) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			all.var->step_y = -1;
			sideDistY = (all.var->pos_y - mapY) * deltaDistY;
		}
		else
		{
			all.var->step_y = 1;
			sideDistY = (mapY + 1.0 - all.var->pos_y) * deltaDistY;
		}
	//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += all.var->step_x;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += all.var->step_y;
				side = 1;
			}
			//Check if ray has hit a wall
			if(map[mapX][mapY] > 0)			// запомните твари 
				hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(side == 0)
			perpWallDist = (mapX - all.var->pos_x + (1 - all.var->step_x) / 2) / rayDirX;
		else
			perpWallDist = (mapY - all.var->pos_y + (1 - all.var->step_y) / 2) / rayDirY;

      	//Calculate height of line to draw on screen
		int lineHeight = (int)(img_height / perpWallDist);
		
		//calculate lowest and highest pixel to fill in current stripe
		all.var->draw_start = -lineHeight / 2 + img_height / 2;
		if(all.var->draw_start < 0)
			all.var->draw_start = 0;
		all.var->draw_end = lineHeight / 2 + img_height / 2;
		if(all.var->draw_end >= img_height)
			all.var->draw_end = img_height - 1;
		
		// float moveSpeed = 0.3;
		
		// 		while (y < img_height)
		// 		{
		// 			if (y >= all.var->draw_start && y <= all.var->draw_end)
		// 				my_mlx_pixel_put(all, x, y, 0xFFFFFF);
		// 			y++;
		// 		}
		
		
		int	y = 0;
		while (y < img_height)								//coloring walls
		{
			if (y < all.var->draw_start) 					//ceiling
				my_mlx_pixel_put(all.data, x, y, 0x333333);
			if (y > all.var->draw_end) 								//floor
				my_mlx_pixel_put(all.data, x, y, 0xAAAAAA);
				
		// 		//textures
		// 	if (y >= all.var->draw_start && y <= all.var->draw_end)
		// 	{
		// 		all.var->tex_y = (int)all.var->tex_pos & (tex_height - 1);
		// 		all.var->tex_pos += all.var->step;
		// 		if (all.var->side == 0)
		// 		{
		// 				if (all.var->step_x > 0)
		// 				{
		// 					int color = my_mlx_pixel_take(all.tex_north, all.var->tex_x, all.var->tex_y);
		// 					my_mlx_pixel_put(all.data, x, y, color);
		// 				}
		// 				else if (all.var->step_x < 0)
		// 				{
		// 					int color = my_mlx_pixel_take(all.tex_south, all.var->tex_x, all.var->tex_y);
		// 					my_mlx_pixel_put(all.data, x, y, color);
		// 				}
		// 			}
		// 			if (all.var->side == 1)
		// 			{
		// 				if (all.var->step_y > 0)
		// 				{
		// 					int color = my_mlx_pixel_take(all.tex_west, all.var->tex_x, all.var->tex_y);
		// 					my_mlx_pixel_put(all.data, x, y, color);
		// 				}
		// 				else if (all.var->step_y < 0)
		// 				{
		// 					int color = my_mlx_pixel_take(all.tex_east, all.var->tex_x, all.var->tex_y);
		// 					my_mlx_pixel_put(all.data, x, y, color);
		// 				}
		// 			}
		// 		}
		// 		y++;
		// }
		
			if (y >= all.var->draw_start && y <= all.var->draw_end)
			{
				if (side == 0)				// S N
				{
					if (all.var->dir_x >= 0)
						my_mlx_pixel_put(all.data, x, y, 0xFF0000); // s - red
					else if (all.var->dir_x < 0)
						my_mlx_pixel_put(all.data, x, y, 0x00FF00); // n - green
				}
				if (side == 1)				// W E
				{
					if (all.var->dir_y >= 0)
						my_mlx_pixel_put(all.data, x, y, 0x0000FF); // w - blue
					else if (all.var->dir_y < 0)
						my_mlx_pixel_put(all.data, x, y, 0xFFFFFF);	// e - white
				}
			}
			y++;
		}
		
	// 	      //calculate value of wallX
	// double wallX; //where exactly the wall was hit
	// if(side == 0) wallX = posY + perpWallDist * rayDirY;
	// else          wallX = posX + perpWallDist * rayDirX;
	// wallX -= floor((wallX));

    //   //x coordinate on the texture
	// int texX = int(wallX * double(texWidth));
	// if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
	// if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

    //   // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
    //   // How much to increase the texture coordinate per screen pixel
	// double step = 1.0 * texHeight / lineHeight;
    //   // Starting texture coordinate
	// double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
	// 	for(int y = drawStart; y < drawEnd; y++)
    //   {
    //     // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
    //     int texY = (int)texPos & (texHeight - 1);
    //     texPos += step;
    //     Uint32 color = texture[texNum][texHeight * texY + texX];
    //     //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
    //     if(side == 1) color = (color >> 1) & 8355711;
    //     buffer[y][x] = color;
    //   }
		
		x++;
	}	
}

void	rotate_right(t_all *all)
{
	//rotate to the right
    //both camera direction and camera plane must be rotated
    all->var->old_dir_x = all->var->dir_x;
    all->var->dir_x = all->var->dir_x * cos(-all->var->rot_speed) - all->var->dir_y * sin(-all->var->rot_speed);
    all->var->dir_y = all->var->old_dir_x * sin(-all->var->rot_speed) + all->var->dir_y * cos(-all->var->rot_speed);
    all->var->old_plane_x = all->var->plane_x;
    all->var->plane_x = all->var->plane_x * cos(-all->var->rot_speed) - all->var->plane_y * sin(-all->var->rot_speed);
    all->var->plane_y = all->var->old_plane_x * sin(-all->var->rot_speed) + all->var->plane_y * cos(-all->var->rot_speed);
   
}
	
void	rotate_left(t_all *all)
{
	//rotate to the left
    //both camera direction and camera plane must be rotated
	all->var->old_dir_x = all->var->dir_x;
    all->var->dir_x = all->var->dir_x * cos(all->var->rot_speed) - all->var->dir_y * sin(all->var->rot_speed);
    all->var->dir_y = all->var->old_dir_x * sin(all->var->rot_speed) + all->var->dir_y * cos(all->var->rot_speed);
    all->var->old_plane_x = all->var->plane_x;
    all->var->plane_x = all->var->plane_x * cos(all->var->rot_speed) - all->var->plane_y * sin(all->var->rot_speed);
    all->var->plane_y = all->var->old_plane_x * sin(all->var->rot_speed) + all->var->plane_y * cos(all->var->rot_speed);
}   

void	move_left(t_all *all)
{
	if(map[(int)(all->var->pos_x - all->var->dir_y * all->var->move_speed)][(int)(all->var->pos_y)] == 0)
		all->var->pos_x -= all->var->dir_y * all->var->move_speed;
	if(map[(int)(all->var->pos_x)][(int)(all->var->pos_y + all->var->dir_x * all->var->move_speed)] == 0)
		all->var->pos_y += all->var->dir_x * all->var->move_speed;
}

void	move_right(t_all *all)
{
	if(map[(int)(all->var->pos_x + all->var->dir_y * all->var->move_speed)][(int)(all->var->pos_y)] == 0)
		all->var->pos_x += all->var->dir_y * all->var->move_speed;
	if(map[(int)(all->var->pos_x)][(int)(all->var->pos_y - all->var->dir_x * all->var->move_speed)] == 0)
		all->var->pos_y -= all->var->dir_x * all->var->move_speed;
}

void	move_forward(t_all *all)
{
	if(map[(int)(all->var->pos_x + all->var->dir_x * all->var->move_speed)][(int)(all->var->pos_y)] == 0)
		all->var->pos_x += all->var->dir_x * all->var->move_speed;
	if(map[(int)(all->var->pos_x)][(int)(all->var->pos_y + all->var->dir_y * all->var->move_speed)] == 0)
		all->var->pos_y += all->var->dir_y * all->var->move_speed;
}

void	move_back(t_all *all)
{
	if(map[(int)(all->var->pos_x - all->var->dir_x * all->var->move_speed)][(int)(all->var->pos_y)] == 0)
		all->var->pos_x -= all->var->dir_x * all->var->move_speed;
	if(map[(int)(all->var->pos_x)][(int)(all->var->pos_y - all->var->dir_y * all->var->move_speed)] == 0)
		all->var->pos_y -= all->var->dir_y * all->var->move_speed;
}

int		key_hook(int keycode, t_all *all)
{
	if (keycode == 53)
		exit(0);
	mlx_destroy_image(all->mlx->mlx_ptr, all->data->img);
	if (keycode == 13)
		move_forward(all);
	if (keycode == 1)
		move_back(all);
	if (keycode == 2)
		move_right(all);
	if (keycode == 0)
		move_left(all);
	if (keycode == 123)
		rotate_left(all);
	if (keycode == 124)
		rotate_right(all);
	all->data->img = mlx_new_image(all->mlx->mlx_ptr, img_width, img_height);
	all->data->addr = mlx_get_data_addr(all->data->img, &all->data->bits_per_pixel, &all->data->line_length, &all->data->endian);
	ft_mlx(*all);
	mlx_put_image_to_window(all->mlx->mlx_ptr, all->mlx->win_ptr, all->data->img, 0, 0);
	return (0);
}

int			main(void)
{
	t_mlx	mlx;
	t_data	data;
	t_data	tex_north;
	void	*img;
	t_var	var = {.pos_x = 22, .pos_y = 12, .dir_x = -1, .dir_y = 1, .plane_x = 0, .plane_y = 0.66, .move_speed = 0.3, .rot_speed = 0.3};
	t_all	all;
	int		tex_w = 64;
	int		tex_h = 64;
	
	all.mlx = &mlx;
	all.data = &data;
	all.var = &var;
	all.tex_north = &tex_north;
	
	all.mlx->mlx_ptr = mlx_init();
	all.mlx->win_ptr = mlx_new_window(all.mlx->mlx_ptr, img_width, img_height, "cub3D");
	all.data->img = mlx_new_image(all.mlx->mlx_ptr, img_width, img_height);
	all.data->addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	all.tex_north->img = mlx_xpm_file_to_image(all.mlx->mlx_ptr, "textures/bluestone.xpm", &tex_w, &tex_h);
	//all.tex_north->addr = mlx_get_data_addr(tex_north.img, &tex_north.bits_per_pixel, &tex_north.line_length, &tex_north.endian);
	
	
	// all.tex_south->img = mlx_xpm_file_to_image(all.mlx->mlx_ptr, "textures/bluestone.xpm", tex_w, tex_h);
	// all.tex_west->img = mlx_xpm_file_to_image(all.mlx->mlx_ptr, "textures/bluestone.xpm", tex_w, tex_h);
	// all.tex_east->img = mlx_xpm_file_to_image(all.mlx->mlx_ptr, "textures/bluestone.xpm", tex_w, tex_h);
	
	ft_mlx(all);
	mlx_put_image_to_window(all.mlx->mlx_ptr, all.mlx->win_ptr, all.data->img, 0, 0);
	mlx_hook(all.mlx->win_ptr, 2, 1L<<0, key_hook, &all);
	//mlx_key_hook(all.mlx->win_ptr, key_hook, &all); 
	mlx_hook(all.mlx->win_ptr, 17, 1L<<0, close_func, 0); //exit on close window
	write(1, "open\n", 5);
	mlx_loop(all.mlx->mlx_ptr);
}
