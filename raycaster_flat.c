/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_flat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:06:15 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/06 13:06:07 by mhogg            ###   ########.fr       */
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
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int map[map_width][map_height]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
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


void	put_sprites(t_all all)
{
	// for(int i = 0; i < all.map.num_sprites; i++)
	// {
	// 	all.sprites[i].distance = ((all.map.pos_x - all.sprites[i].x) * (all.map.pos_x - all.sprites[i].x) +
	// 		(all.map.pos_y - all.sprites[i].y) * (all.map.pos_y - all.sprites[i].y));
	// }
	// sort_sprites(all);
	
	for(int i = 0; i < 1; i++)
	{
		double spriteX = 4 - all.var->pos_x;
		double spriteY = 4 - all.var->pos_y;
	printf("\nspriteX = %.2f, spriteY = %.2f ", spriteX, spriteY);
		double invDet = 1.0 / (all.var->plane_x * all.var->dir_y - all.var->dir_x * all.var->plane_y);
		double transformX = invDet * (all.var->dir_y * spriteX - all.var->dir_x * spriteY);
		double transformY = invDet * (-all.var->plane_y * spriteX + all.var->plane_x * spriteY);
	printf("x = %.2f , y = %.2f ", transformX, transformY);
		int spriteScreenX = (int)((img_width / 2) * (1 + transformX / transformY));
	printf("img_width = %d", img_width);
	printf("spriteScreenX = %d ", spriteScreenX);
		int spriteHeight = abs((int)(img_height / (transformY)));
	printf("spriteHeight = %d ", spriteHeight);
		int drawStartY = -spriteHeight / 2 + img_height / 2;
		if(drawStartY < 0)
			drawStartY = 0;
	printf("drawStartY = %d ", drawStartY);
		int drawEndY = spriteHeight / 2 + img_height / 2;
		if(drawEndY >= img_height)
			drawEndY = img_height - 1;
	printf("drawEndY = %d ", drawEndY);
		int spriteWidth = abs((int) (img_height / (transformY)));
	printf("spriteWidth = %d ", spriteWidth);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
	printf("drawStartX = %d ", drawStartX);
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= img_width)
			drawEndX = img_width - 1;
	printf("drawEndXY = %d ", drawEndX);
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
		int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * 64 / spriteWidth) / 256;
			if(transformY > 0 && stripe > 0 && stripe < img_width)// && transformY < all.map.every_dist[stripe])
			{
				for(int y = drawStartY; y < drawEndY; y++)
				{
					int d = (y) * 256 - img_height * 128 + spriteHeight * 128;
					int texY = ((d * 64) / spriteHeight) / 256;
					int color = my_mlx_pixel_take(all.sprite, texX, texY);
					if (color)
						my_mlx_pixel_put(all.data, stripe, y, color);
				}
			}
		}
	}
}

void	ft_mlx(t_all all)
{
	int x = 0;

	while (x < img_width)
    {
 		//calculate ray position and direction
 		double camera_x = 2 * x / (double)img_width - 1; //x-coordinate in camera space
 		double rayDirX = all.var->dir_x + all.var->plane_x * camera_x;
 		double rayDirY = all.var->dir_y + all.var->plane_y * camera_x;
 		//which box of the map we're in
 		all.var->map_x = (int)all.var->pos_x;
 		all.var->map_y = (int)all.var->pos_y;

       //length of ray from one x or y-side to next x or y-side
		all.var->delta_distx = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		all.var->delta_disty = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));

		double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
		all.var->hit = 0; //was there a wall hit?
		//was a NS or a EW wall hit?
      //calculate step and initial sideDist
		if(rayDirX < 0)
		{
			all.var->step_x = -1;
			all.var->side_distx = (all.var->pos_x - all.var->map_x) * all.var->delta_distx;
		}
		else
		{
			all.var->step_x = 1;
			all.var->side_distx = (all.var->map_x + 1.0 - all.var->pos_x) * all.var->delta_distx;
		}
		if(rayDirY < 0)
		{
			all.var->step_y = -1;
			all.var->side_disty = (all.var->pos_y - all.var->map_y) * all.var->delta_disty;
		}
		else
		{
			all.var->step_y = 1;
			all.var->side_disty = (all.var->map_y + 1.0 - all.var->pos_y) * all.var->delta_disty;
		}
	//perform DDA
		while (all.var->hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(all.var->side_distx < all.var->side_disty)
			{
				all.var->side_distx += all.var->delta_distx;
				all.var->map_x += all.var->step_x;
				all.var->side = 0;
			}
			else
			{
				all.var->side_disty += all.var->delta_disty;
				all.var->map_y += all.var->step_y;
				all.var->side = 1;
			}
			//Check if ray has hit a wall
			if(map[all.var->map_x][all.var->map_y] > 0)			// запомните твари 
				all.var->hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(all.var->side == 0)
			perpWallDist = (all.var->map_x - all.var->pos_x + (1 - all.var->step_x) / 2) / rayDirX;
		else
			perpWallDist = (all.var->map_y - all.var->pos_y + (1 - all.var->step_y) / 2) / rayDirY;

      	//Calculate height of line to draw on screen
		int lineHeight = (int)(img_height / perpWallDist);
		
		//calculate lowest and highest pixel to fill in current stripe
		all.var->draw_start = -lineHeight / 2 + img_height / 2;
		if(all.var->draw_start < 0)
			all.var->draw_start = 0;
		all.var->draw_end = lineHeight / 2 + img_height / 2;
		if(all.var->draw_end >= img_height)
			all.var->draw_end = img_height - 1;
		
		
		
		// textures start
		double wallX;
		if (all.var->side == 0) 
			wallX = all.var->pos_y + perpWallDist * rayDirY;
    	else	wallX = all.var->pos_x + perpWallDist * rayDirX;
    	wallX -= floor((wallX));  //Функция floor() возвращает наибольшее целое число 

      	//x coordinate on the texture
      	all.var->tex_x = (int)(wallX * (double)(tex_width));
      	if(all.var->side == 0 && rayDirX > 0) 
			all.var->tex_x = tex_width - all.var->tex_x - 1;
      	if(all.var->side == 1 && rayDirY < 0)
			all.var->tex_x = tex_width - all.var->tex_x - 1;
      	all.var->step = 1.0 * tex_height / lineHeight;   // Starting texture coordinate
		all.var->tex_pos = (all.var->draw_start - img_height / 2 + lineHeight / 2) * all.var->step;
	
		int	y = 0;
		int color;
		while (y < img_height)								//coloring walls
		{
			if (y < all.var->draw_start) 					//ceiling
				my_mlx_pixel_put(all.data, x, y, 0x333333);
			if (y > all.var->draw_end) 								//floor
				my_mlx_pixel_put(all.data, x, y, 0xAAAAAA);
			if (y >= all.var->draw_start && y <= all.var->draw_end)  // textures
			{
				all.var->tex_y = (int)all.var->tex_pos & (tex_height - 1);
				all.var->tex_pos += all.var->step;
				if (all.var->side == 0)				// S N
				{
					if (all.var->dir_x >= 0)
					{
						color = my_mlx_pixel_take(all.tex_north, all.var->tex_x, all.var->tex_y);
						my_mlx_pixel_put(all.data, x, y, color);
					// 	my_mlx_pixel_put(all.data, x, y, 0xFF0000); // s - red
					}
					else	if (all.var->dir_x < 0)
					{
						color = my_mlx_pixel_take(all.tex_south, all.var->tex_x, all.var->tex_y);
						my_mlx_pixel_put(all.data, x, y, color);
					//	my_mlx_pixel_put(all.data, x, y, 0x00FF00); // n - green
					}
				}
				if (all.var->side == 1)			// W E	
				{
					if (all.var->dir_y >= 0)
					{
						color = my_mlx_pixel_take(all.tex_west, all.var->tex_x, all.var->tex_y);
						my_mlx_pixel_put(all.data, x, y, color);
						//my_mlx_pixel_put(all.data, x, y, 0x0000FF); // w - blue
					}
					else if (all.var->dir_y < 0)
					{
						color = my_mlx_pixel_take(all.tex_east, all.var->tex_x, all.var->tex_y);
						my_mlx_pixel_put(all.data, x, y, color);
						//my_mlx_pixel_put(all.data, x, y, 0xFFFFFF);	// e - white
					}
				}
			}
			y++;
		}
		x++;
	}
}

void	rotate_right(t_all *all)
{
    all->var->old_dir_x = all->var->dir_x;
    all->var->dir_x = all->var->dir_x * cos(-all->var->rot_speed) - all->var->dir_y * sin(-all->var->rot_speed);
    all->var->dir_y = all->var->old_dir_x * sin(-all->var->rot_speed) + all->var->dir_y * cos(-all->var->rot_speed);
    all->var->old_plane_x = all->var->plane_x;
    all->var->plane_x = all->var->plane_x * cos(-all->var->rot_speed) - all->var->plane_y * sin(-all->var->rot_speed);
    all->var->plane_y = all->var->old_plane_x * sin(-all->var->rot_speed) + all->var->plane_y * cos(-all->var->rot_speed);
}
	
void	rotate_left(t_all *all)
{
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
	put_sprites(*all);
	mlx_put_image_to_window(all->mlx->mlx_ptr, all->mlx->win_ptr, all->data->img, 0, 0);
	return (0);
}

int			main(void)
{
	t_mlx	mlx;
	t_data	data;
	t_data	tex_north;
	t_data	tex_south;
	t_data	tex_west;
	t_data	tex_east;
	t_data	sprite;
	void	*img;
	t_var	var = {.pos_x = 5, .pos_y = 5, .dir_x = -1, .dir_y = 1, .plane_x = 0, .plane_y = 0.66, .move_speed = 0.3, .rot_speed = 0.3};
	t_all	all;
	int		tex_w;
	int		tex_h;
	// int		sprite_w;
	// int		sprite_h;
	
	all.sprite = &sprite;
	all.mlx = &mlx;
	all.data = &data;
	all.var = &var;
	all.tex_north = &tex_north;
	all.tex_south = &tex_south;
	all.tex_west = &tex_west;
	all.tex_east = &tex_east;
	
	all.mlx->mlx_ptr = mlx_init();
	all.mlx->win_ptr = mlx_new_window(all.mlx->mlx_ptr, img_width, img_height, "cub3D");
	all.data->img = mlx_new_image(all.mlx->mlx_ptr, img_width, img_height);
	all.data->addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	all.tex_north->img = mlx_xpm_file_to_image(all.mlx->mlx_ptr, "textures/bluestone.xpm", &tex_w, &tex_h);
	all.tex_north->addr = mlx_get_data_addr(tex_north.img, &tex_north.bits_per_pixel, &tex_north.line_length, &tex_north.endian);
	all.tex_south->img = mlx_xpm_file_to_image(all.mlx->mlx_ptr, "textures/redbrick.xpm", &tex_w, &tex_h);
	all.tex_south->addr = mlx_get_data_addr(tex_south.img, &tex_south.bits_per_pixel, &tex_south.line_length, &tex_south.endian);
	all.tex_west->img = mlx_xpm_file_to_image(all.mlx->mlx_ptr, "textures/ahs6x-6ayyg.xpm", &tex_w, &tex_h);
	all.tex_west->addr = mlx_get_data_addr(tex_west.img, &tex_west.bits_per_pixel, &tex_west.line_length, &tex_west.endian);
	all.tex_east->img = mlx_xpm_file_to_image(all.mlx->mlx_ptr, "textures/awwhg-cbk2w.xpm", &tex_w, &tex_h);
	all.tex_east->addr = mlx_get_data_addr(tex_east.img, &tex_east.bits_per_pixel, &tex_east.line_length, &tex_east.endian);
	all.sprite->img = mlx_xpm_file_to_image(all.mlx->mlx_ptr, "textures/sprite.xpm", &tex_w, &tex_h);
	all.sprite->addr = mlx_get_data_addr(sprite.img, &sprite.bits_per_pixel, &sprite.line_length, &sprite.endian);

	//mlx_xpm_file_to_image(all.mlx->mlx_ptr, "textures/bluestone.xpm", tex_w, tex_h);
	
	ft_mlx(all);
	mlx_put_image_to_window(all.mlx->mlx_ptr, all.mlx->win_ptr, all.data->img, 0, 0);
	mlx_hook(all.mlx->win_ptr, 2, 1L<<0, key_hook, &all);
	//mlx_key_hook(all.mlx->win_ptr, key_hook, &all); 
	mlx_hook(all.mlx->win_ptr, 17, 1L<<0, close_func, 0); //exit on close window
	write(1, "open\n", 5);
	mlx_loop(all.mlx->mlx_ptr);
}
