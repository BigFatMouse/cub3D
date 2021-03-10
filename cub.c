/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:06:15 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/11 00:43:17 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int map[map_width][map_height]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1},
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

void	rotate_left_right(t_all all, int keycode)
{
    if (keycode == 124)
	{
		all.var->old_dir_x = all.var->dir_x;
		all.var->dir_x = all.var->dir_x * cos(-all.var->rot_speed) - all.var->dir_y * sin(-all.var->rot_speed);
 		all.var->dir_y = all.var->old_dir_x * sin(-all.var->rot_speed) + all.var->dir_y * cos(-all.var->rot_speed);
		all.var->old_plane_x = all.var->plane_x;
		all.var->plane_x = all.var->plane_x * cos(-all.var->rot_speed) - all.var->plane_y * sin(-all.var->rot_speed);
		all.var->plane_y = all.var->old_plane_x * sin(-all.var->rot_speed) + all.var->plane_y * cos(-all.var->rot_speed);
	}
	if (keycode == 123)
	{
		all.var->old_dir_x = all.var->dir_x;
		all.var->dir_x = all.var->dir_x * cos(all.var->rot_speed) - all.var->dir_y * sin(all.var->rot_speed);
		all.var->dir_y = all.var->old_dir_x * sin(all.var->rot_speed) + all.var->dir_y * cos(all.var->rot_speed);
		all.var->old_plane_x = all.var->plane_x;
		all.var->plane_x = all.var->plane_x * cos(all.var->rot_speed) - all.var->plane_y * sin(all.var->rot_speed);
		all.var->plane_y = all.var->old_plane_x * sin(all.var->rot_speed) + all.var->plane_y * cos(all.var->rot_speed);
	}
}

void	move_left_rigth(t_all all, int keycode)
{
	if (keycode == 0)
	{
		if(all.scene->map[(int)(all.var->pos_x - all.var->dir_y * all.var->move_speed)][(int)(all.var->pos_y)] == '0')
			all.var->pos_x -= all.var->dir_y * all.var->move_speed;
		if(all.scene->map[(int)(all.var->pos_x)][(int)(all.var->pos_y + all.var->dir_x * all.var->move_speed)] == '0')
			all.var->pos_y += all.var->dir_x * all.var->move_speed;
	}
	if (keycode == 2)
	{
		if(all.scene->map[(int)(all.var->pos_x + all.var->dir_y * all.var->move_speed)][(int)(all.var->pos_y)] == '0')
			all.var->pos_x += all.var->dir_y * all.var->move_speed;
		if(all.scene->map[(int)(all.var->pos_x)][(int)(all.var->pos_y - all.var->dir_x * all.var->move_speed)] == '0')
			all.var->pos_y -= all.var->dir_x * all.var->move_speed;
	}
}

void	move_back_forward(t_all all, int keycode)
{
	if (keycode == 13)
	{
		if(all.scene->map[(int)(all.var->pos_x + all.var->dir_x * all.var->move_speed)][(int)(all.var->pos_y)] == '0')
			all.var->pos_x += all.var->dir_x * all.var->move_speed;
		if(all.scene->map[(int)(all.var->pos_x)][(int)(all.var->pos_y + all.var->dir_y * all.var->move_speed)] == '0')
			all.var->pos_y += all.var->dir_y * all.var->move_speed;
	}
	if (keycode == 1)
	{
		if(all.scene->map[(int)(all.var->pos_x - all.var->dir_x * all.var->move_speed)][(int)(all.var->pos_y)] == '0')
			all.var->pos_x -= all.var->dir_x * all.var->move_speed;
		if(all.scene->map[(int)(all.var->pos_x)][(int)(all.var->pos_y - all.var->dir_y * all.var->move_speed)] == '0')
			all.var->pos_y -= all.var->dir_y * all.var->move_speed;
	}
}

int		key_hook(int keycode, t_all *all)
{
	if (keycode == 53)
		exit(0);
	mlx_destroy_image(all->mlx->mlx_ptr, all->data->img);
	if (keycode == 13 || keycode == 1)
		move_back_forward(*all, keycode);
	if (keycode == 2 || keycode == 0)
		move_left_rigth(*all, keycode);
	if (keycode == 123 || keycode == 124)
		rotate_left_right(*all, keycode);
	all->data->img = mlx_new_image(all->mlx->mlx_ptr, all->scene->i_width, all->scene->i_height);
	all->data->addr = mlx_get_data_addr(all->data->img, &all->data->bits_per_pixel, &all->data->line_length, &all->data->endian);
	put_scene(*all);
	put_sprites(*all);
	mlx_put_image_to_window(all->mlx->mlx_ptr, all->mlx->win_ptr, all->data->img, 0, 0);
	return (0);
}

int		close_func(void)
{
	exit(0);
}

/*------------------- end of key_hooks.c ----------------------*/


/*-------------------- mlx_funcs.c -----------------------------*/

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

/*-------------------- end of mlx_funcs.c -----------------------------*/

/*-------------------- put_sprites.c ----------------------------------*/

void	put_sprites(t_all all)
{
	int i = -1;
	while (++i < all.scene->spr_num)  // calculate distance
		all.sprite[i].dist = ((all.var->pos_x - all.sprite[i].x) * (all.var->pos_x - all.sprite[i].x) +
			(all.var->pos_y - all.sprite[i].y) * (all.var->pos_y - all.sprite[i].y));
	//sort_sprites(all);

	for(int i = 0; i < all.scene->spr_num; i++)
	{
		double spriteX = all.sprite[i].x - all.var->pos_x;
		double spriteY = all.sprite[i].y - all.var->pos_y;
		double invDet = 1.0 / (all.var->plane_x * all.var->dir_y - all.var->dir_x * all.var->plane_y);
		double transformX = invDet * (all.var->dir_y * spriteX - all.var->dir_x * spriteY);
		double transformY = invDet * (-all.var->plane_y * spriteX + all.var->plane_x * spriteY);
		int spriteScreenX = (int)((all.scene->i_width / 2) * (1 + transformX / transformY));
		int spriteHeight = abs((int)(all.scene->i_height / transformY * all.var->asp_ratio));
		int drawStartY = -spriteHeight / 2 + all.scene->i_height / 2;
		if(drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + all.scene->i_height / 2;
		if(drawEndY >= all.scene->i_height)
			drawEndY = all.scene->i_height - 1;
		int spriteWidth = abs((int)(all.scene->i_height / transformY * all.var->asp_ratio));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= all.scene->i_width)
			drawEndX = all.scene->i_width - 1;
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
		int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * 64 / spriteWidth) / 256;
			if(transformY > 0 && stripe > 0 && stripe < all.scene->i_width && transformY) // < global->map.every_dist[stripe])
			{
				for(int y = drawStartY; y < drawEndY; y++)
				{
					int d = (y) * 256 - all.scene->i_height * 128 + spriteHeight * 128;
					int texY = ((d * 64) / spriteHeight) / 256;
					int color = my_mlx_pixel_take(all.sprite_img, texX, texY);
					if (color)
						my_mlx_pixel_put(all.data, stripe, y, color);
				}
			}
		}
	}
}

/*-------------------- end of put_sprites.c -----------------------------*/

/*----------------------- draw_scene.c ----------------------------------*/

void	calculate_ray(t_all all, int x)
{
	//calculate ray position and direction
 		double camera_x = 2 * x / (double)all.scene->i_width - 1; //x-coordinate in camera space
 		all.var->ray_dir_x = all.var->dir_x + all.var->plane_x * camera_x;
 		all.var->ray_dir_y = all.var->dir_y + all.var->plane_y * camera_x;
 		//which box of the map we're in
 		all.var->map_x = (int)all.var->pos_x;
 		all.var->map_y = (int)all.var->pos_y;

       //length of ray from one x or y-side to next x or y-side
		all.var->delta_distx = sqrt(1 + (all.var->ray_dir_y * all.var->ray_dir_y) / (all.var->ray_dir_x * all.var->ray_dir_x));
		all.var->delta_disty = sqrt(1 + (all.var->ray_dir_x * all.var->ray_dir_x) / (all.var->ray_dir_y * all.var->ray_dir_y));

		//double all.var->perp_wall_dist;
		all.var->hit = 0; //was there a wall hit?
		
}

void	calculate_step_dist(t_all all, int x)
{
	if(all.var->ray_dir_x < 0)
		{
			all.var->step_x = -1;
			all.var->side_distx = (all.var->pos_x - all.var->map_x) * all.var->delta_distx;
		}
		else
		{
			all.var->step_x = 1;
			all.var->side_distx = (all.var->map_x + 1.0 - all.var->pos_x) * all.var->delta_distx;
		}
		if(all.var->ray_dir_y < 0)
		{
			all.var->step_y = -1;
			all.var->side_disty = (all.var->pos_y - all.var->map_y) * all.var->delta_disty;
		}
		else
		{
			all.var->step_y = 1;
			all.var->side_disty = (all.var->map_y + 1.0 - all.var->pos_y) * all.var->delta_disty;
		}
}

void	perform_dda(t_all all, int x)
{
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
			if(all.scene->map[all.var->map_x][all.var->map_y] == '1')			// запомните твари 
				all.var->hit = 1;
		}
}

void	put_scene(t_all all)
{
	int x = 0;

	while (x < all.scene->i_width)
    {
 		calculate_ray(all, x);
		calculate_step_dist(all, x);
		perform_dda(all, x);
		
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(all.var->side == 0)
			all.var->perp_wall_dist = (all.var->map_x - all.var->pos_x + (1 - all.var->step_x) / 2) / all.var->ray_dir_x;
		else
			all.var->perp_wall_dist = (all.var->map_y - all.var->pos_y + (1 - all.var->step_y) / 2) / all.var->ray_dir_y;
		all.var->asp_ratio = 0.75 * all.scene->i_width / all.scene->i_height;
      	//Calculate height of line to draw on screen
		int lineHeight = (int)(all.scene->i_height / all.var->perp_wall_dist * all.var->asp_ratio);
		//global->map.every_dist[x] = global->draw.perp_wall_dist;
		//calculate lowest and highest pixel to fill in current stripe
		all.var->draw_start = -lineHeight / 2 + all.scene->i_height / 2;
		if(all.var->draw_start < 0)
			all.var->draw_start = 0;
		all.var->draw_end = lineHeight / 2 + all.scene->i_height / 2;
		if(all.var->draw_end >= all.scene->i_height)
			all.var->draw_end = all.scene->i_height - 1;
		
		
		
		// textures start
		double wallX;
		if (all.var->side == 0) 
			wallX = all.var->pos_y + all.var->perp_wall_dist * all.var->ray_dir_y;
    	else	wallX = all.var->pos_x + all.var->perp_wall_dist * all.var->ray_dir_x;
    	wallX -= floor((wallX));  //Функция floor() возвращает наибольшее целое число 

      	//x coordinate on the texture
      	all.var->tex_x = (int)(wallX * (double)(tex_width));
      	if(all.var->side == 0 && all.var->ray_dir_x > 0) 
			all.var->tex_x = tex_width - all.var->tex_x - 1;
      	if(all.var->side == 1 && all.var->ray_dir_y < 0)
			all.var->tex_x = tex_width - all.var->tex_x - 1;
      	all.var->step = 1.0 * tex_height / lineHeight;   // Starting texture coordinate
		all.var->tex_pos = (all.var->draw_start - all.scene->i_height / 2 + lineHeight / 2) * all.var->step;
	
		int	y = 0;
		int color;
		while (y < all.scene->i_height)								//coloring walls
		{
			if (y < all.var->draw_start) 					//ceiling
				my_mlx_pixel_put(all.data, x, y, all.scene->floor_color);
			if (y > all.var->draw_end) 								//floor
				my_mlx_pixel_put(all.data, x, y, all.scene->ceill_color);
			if (y >= all.var->draw_start && y <= all.var->draw_end)  // textures
			{
				all.var->tex_y = (int)all.var->tex_pos & (tex_height - 1);
				all.var->tex_pos += all.var->step;
				if (all.var->side == 0)				// S N
				{
					if (all.var->step_x > 0)
					{
						color = my_mlx_pixel_take(all.texsouth_img, all.var->tex_x, all.var->tex_y);
						my_mlx_pixel_put(all.data, x, y, color);
					// 	my_mlx_pixel_put(all.data, x, y, 0xFF0000); // s - red
					}
					else	if (all.var->step_x < 0)
					{
						color = my_mlx_pixel_take(all.texnorth_img, all.var->tex_x, all.var->tex_y);
						my_mlx_pixel_put(all.data, x, y, color);
					//	my_mlx_pixel_put(all.data, x, y, 0x00FF00); // n - green
					}
				}
				if (all.var->side == 1)			// W E	
				{
					if (all.var->step_y > 0)
					{
						color = my_mlx_pixel_take(all.texeast_img, all.var->tex_x, all.var->tex_y);
						my_mlx_pixel_put(all.data, x, y, color);
						//my_mlx_pixel_put(all.data, x, y, 0x0000FF); // w - blue
					}
					else if (all.var->step_y < 0)
					{
						color = my_mlx_pixel_take(all.texwest_img, all.var->tex_x, all.var->tex_y);
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



int			main(void)
{
	t_mlx		mlx;
	t_data		data;
	t_data		texnorth_img;
	t_data		texsouth_img;
	t_data		texwest_img;
	t_data		texeast_img;
	t_data		sprite_img;
	t_sprite	*sprite;
	t_scene		scene; // = {.i_width = 640, .i_height = 480};
	t_parce		flags;
	t_var		var = {.pos_x = 5, .pos_y = 5, .dir_x = -1, .dir_y = 1, .plane_x = 0, .plane_y = 0.66, .move_speed = 0.3, .rot_speed = 0.3};
	t_all		all;
	int			tex_w;
	int			tex_h;
	
	all.sprite_img = &sprite_img;
	all.sprite = sprite;
	all.mlx = &mlx;
	all.data = &data;
	all.var = &var;
	all.texnorth_img = &texnorth_img;
	all.texsouth_img = &texsouth_img;
	all.texwest_img = &texwest_img;
	all.texeast_img = &texeast_img;
	all.scene = &scene;
	all.flags = &flags;
	
	// all.scene->spr_num = 3;
	
	// all.sprite[0].x = 2;
	// all.sprite[0].y = 5;
	// all.sprite[1].x = 2;
	// all.sprite[1].y = 7;
	// all.sprite[2].x = 2;
	// all.sprite[2].y = 15;
	
	int		fd = open("scene.cub", O_RDONLY);
	struct_flags_init(&all);
	parcer(fd, &all);
	printf("west: %s\n", all.scene->tex_west_file);
	
	
	all.mlx->mlx_ptr = mlx_init();
	all.mlx->win_ptr = mlx_new_window(all.mlx->mlx_ptr, all.scene->i_width, all.scene->i_height, "cub3D");
	all.data->img = mlx_new_image(all.mlx->mlx_ptr, all.scene->i_width, all.scene->i_height);
	all.data->addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	all.texnorth_img->img = mlx_xpm_file_to_image(all.mlx->mlx_ptr, all.scene->tex_north_file, &tex_w, &tex_h);
	all.texnorth_img->addr = mlx_get_data_addr(texnorth_img.img, &texnorth_img.bits_per_pixel, &texnorth_img.line_length, &texnorth_img.endian);
	all.texsouth_img->img = mlx_xpm_file_to_image(all.mlx->mlx_ptr, all.scene->tex_south_file, &tex_w, &tex_h);
	all.texsouth_img->addr = mlx_get_data_addr(texsouth_img.img, &texsouth_img.bits_per_pixel, &texsouth_img.line_length, &texsouth_img.endian);
	all.texwest_img->img = mlx_xpm_file_to_image(all.mlx->mlx_ptr, all.scene->tex_west_file, &tex_w, &tex_h);
	all.texwest_img->addr = mlx_get_data_addr(texwest_img.img, &texwest_img.bits_per_pixel, &texwest_img.line_length, &texwest_img.endian);
	printf("east: %s\n", all.scene->tex_east_file);
	// if(!mlx_xpm_file_to_image(all.mlx->mlx_ptr, all.scene->tex_east_file, &tex_w, &tex_h))
	// 	ft_error(ERR_CODE_3);
	if(!(all.texeast_img->img = mlx_xpm_file_to_image(all.mlx->mlx_ptr, all.scene->tex_east_file, &tex_w, &tex_h)))
		ft_error(ERR_CODE_3);
	all.texeast_img->addr = mlx_get_data_addr(texeast_img.img, &texeast_img.bits_per_pixel, &texeast_img.line_length, &texeast_img.endian);
	
	// if (!mlx_xpm_file_to_image(all.mlx->mlx_ptr, all.scene->sprite_file, &tex_w, &tex_h))
	// 	ft_error(ERR_CODE_4);
	all.sprite_img->img = mlx_xpm_file_to_image(all.mlx->mlx_ptr, all.scene->sprite_file, &tex_w, &tex_h);
	all.sprite_img->addr = mlx_get_data_addr(sprite_img.img, &sprite_img.bits_per_pixel, &sprite_img.line_length, &sprite_img.endian);
	
	put_scene(all);
	mlx_put_image_to_window(all.mlx->mlx_ptr, all.mlx->win_ptr, all.data->img, 0, 0);
	mlx_hook(all.mlx->win_ptr, 2, 1L<<0, key_hook, &all);
	//mlx_key_hook(all.mlx->win_ptr, key_hook, &all); 
	mlx_hook(all.mlx->win_ptr, 17, 1L<<0, close_func, 0); //exit on close window
	write(1, "open\n", 5);
	mlx_loop(all.mlx->mlx_ptr);
}
