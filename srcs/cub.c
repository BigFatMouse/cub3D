/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:06:15 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/12 18:57:05 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		close_func(void)
{
	exit(0);
}

void	ft_error(char *str)
{
	write(2, "/n", 1);
	ft_putendl_fd(str, 2);
	exit(1);
}

void		check_screen_size(t_all all)
{
	int max_width;
	int max_height;

	mlx_get_screen_size(all.mlx->mlx_ptr, &max_width, &max_height);
	if (all.scene->i_width > max_width)
		all.scene->i_width = max_width;
	if (all.scene->i_height > max_height)
		all.scene->i_height = max_height;
}


void	calculate_ray(t_all all, int x)
{
 	double camera_x;
	camera_x = 2 * x / (double)all.scene->i_width - 1;
 	all.var->ray_dir_x = all.var->dir_x + all.var->plane_x * camera_x;
 	all.var->ray_dir_y = all.var->dir_y + all.var->plane_y * camera_x;
 	all.var->map_x = (int)all.var->pos_x;
 	all.var->map_y = (int)all.var->pos_y;
	all.var->delta_distx = sqrt(1 + (all.var->ray_dir_y * all.var->ray_dir_y) /
							(all.var->ray_dir_x * all.var->ray_dir_x));
	all.var->delta_disty = sqrt(1 + (all.var->ray_dir_x * all.var->ray_dir_x) /
							(all.var->ray_dir_y * all.var->ray_dir_y));
	all.var->hit = 0; 
		
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
		if(all.scene->map[all.var->map_x][all.var->map_y] == '1')			// запомните твари 
			all.var->hit = 1;
	}
}

void	texture_start(t_all all)
{
	double wallX;
	int tex_width;
	int tex_height;
	
	tex_height = 64;
	tex_width = 64;
	if (all.var->side == 0) 
		wallX = all.var->pos_y + all.var->perp_wall_dist * all.var->ray_dir_y;
    else	wallX = all.var->pos_x + all.var->perp_wall_dist * all.var->ray_dir_x;
    	wallX -= floor((wallX));
    all.var->tex_x = (int)(wallX * (double)(tex_width));
    if(all.var->side == 0 && all.var->ray_dir_x > 0) 
		all.var->tex_x = tex_width - all.var->tex_x - 1;
    if(all.var->side == 1 && all.var->ray_dir_y < 0)
		all.var->tex_x = tex_width - all.var->tex_x - 1;
    all.var->step = 1.0 * tex_height / all.var->line_height;
	all.var->tex_pos = (all.var->draw_start - all.scene->i_height / 2 + all.var->line_height / 2) * all.var->step;
}

void	calculate_sides(t_all all, int x)
{
	if(all.var->side == 0)
		all.var->perp_wall_dist = (all.var->map_x - all.var->pos_x +
		(1 - all.var->step_x) / 2) / all.var->ray_dir_x;
	else
		all.var->perp_wall_dist = (all.var->map_y - all.var->pos_y +
		(1 - all.var->step_y) / 2) / all.var->ray_dir_y;
	all.var->z_buffer[x] = all.var->perp_wall_dist;
	all.var->asp_ratio = 0.75 * all.scene->i_width / all.scene->i_height;
	all.var->line_height = (int)(all.scene->i_height /
							all.var->perp_wall_dist * all.var->asp_ratio);
	all.var->draw_start = -all.var->line_height / 2 + all.scene->i_height / 2;
	if(all.var->draw_start < 0)
		all.var->draw_start = 0;
	all.var->draw_end = all.var->line_height / 2 + all.scene->i_height / 2;
	if(all.var->draw_end >= all.scene->i_height)
		all.var->draw_end = all.scene->i_height - 1;
}

void	put_west_east(t_all all, int x, int y)
{
	int color;
	
	if (all.var->side == 1)
	{
		if (all.var->step_y > 0)
		{
			color = my_mlx_pixel_take(all.texeast_img, all.var->tex_x, all.var->tex_y);
			my_mlx_pixel_put(all.data, x, y, color);
		}
		else if (all.var->step_y < 0)
		{
			color = my_mlx_pixel_take(all.texwest_img, all.var->tex_x, all.var->tex_y);
			my_mlx_pixel_put(all.data, x, y, color);
		}
	}
}

void	put_north_south(t_all all, int x, int y)
{
	int color;
	
	if (all.var->side == 0)
	{
		if (all.var->step_x > 0)
		{
			color = my_mlx_pixel_take(all.texsouth_img, all.var->tex_x, all.var->tex_y);
			my_mlx_pixel_put(all.data, x, y, color);
		}
		else	if (all.var->step_x < 0)
		{
			color = my_mlx_pixel_take(all.texnorth_img, all.var->tex_x, all.var->tex_y);
			my_mlx_pixel_put(all.data, x, y, color);
		}
	}
}

void	put_scene(t_all all)
{
	int x;
	int	y;
	int color;
	int	tex_height;
	
	tex_height = 64;
	x = -1;
	while (++x < all.scene->i_width)
    {
 		calculate_ray(all, x);
		calculate_step_dist(all, x);
		perform_dda(all, x);
		calculate_sides(all, x);
		texture_start(all);
		y = -1;
		while (++y < all.scene->i_height)
		{
			if (y < all.var->draw_start)
				my_mlx_pixel_put(all.data, x, y, all.scene->floor_color);
			if (y > all.var->draw_end)
				my_mlx_pixel_put(all.data, x, y, all.scene->ceill_color);
			if (y >= all.var->draw_start && y <= all.var->draw_end)
			{
				all.var->tex_y = (int)all.var->tex_pos & (tex_height - 1);
				all.var->tex_pos += all.var->step;
				put_north_south(all, x, y);
				put_west_east(all, x, y);
			}
		}
	}
}

void	parce_args(t_all all, int argc, char **argv)
{
	if (argc == 2)
	{
		
	}
	if (argc == 3)
	{
		if (!ft_strncmp(argv[2], "--save", 6))
		{
			all.flags->screenshot = 1;
			ft_putendl_fd("\nImage saved", 1);
		}
		else
			ft_error(ERR_CODE_10);
	}
	else
		ft_error(ERR_CODE_9);
}

int		main(int argc, char **argv)
{
	int			fd;
	
	t_mlx		mlx;
	t_data		data;
	t_data		texnorth_img;
	t_data		texsouth_img;
	t_data		texwest_img;
	t_data		texeast_img;
	t_data		sprite_img;
	t_sprite	*sprite;
	t_scene		scene;
	t_parce		flags;
	t_var		var = {.pos_x = 4.5, .pos_y = 4.5, .dir_x = -1, .dir_y = 1, .plane_x = 0, .plane_y = 0.66, .move_speed = 0.3, .rot_speed = 0.3};
	t_all		all;
	int			width;
	int			height;
	
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

	struct_flags_init(&all);
	parce_args(all, argc, argv);
	fd = open(argv[1], O_RDONLY);
	parcer(fd, &all);
	
	
	
	
	if(!(all.var->z_buffer = malloc(sizeof(double) * all.scene->i_width)))
		ft_error(ERR_CODE_0);
	all.mlx->mlx_ptr = mlx_init();
	check_screen_size(all);
	all.mlx->win_ptr = mlx_new_window(all.mlx->mlx_ptr, all.scene->i_width, all.scene->i_height, "cub3D");
	all.data->img = mlx_new_image(all.mlx->mlx_ptr, all.scene->i_width, all.scene->i_height);
	all.data->addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	if(!(all.texnorth_img->img = mlx_xpm_file_to_image(all.mlx->mlx_ptr, all.scene->tex_north_file, &width, &height)))
		ft_error(ERR_CODE_3);
	all.texnorth_img->addr = mlx_get_data_addr(texnorth_img.img, &texnorth_img.bits_per_pixel, &texnorth_img.line_length, &texnorth_img.endian);
	if(!(all.texsouth_img->img = mlx_xpm_file_to_image(all.mlx->mlx_ptr, all.scene->tex_south_file, &width, &height)))
		ft_error(ERR_CODE_3);
	all.texsouth_img->addr = mlx_get_data_addr(texsouth_img.img, &texsouth_img.bits_per_pixel, &texsouth_img.line_length, &texsouth_img.endian);
	if(!(all.texwest_img->img = mlx_xpm_file_to_image(all.mlx->mlx_ptr, all.scene->tex_west_file, &width, &height)))
		ft_error(ERR_CODE_3);
	all.texwest_img->addr = mlx_get_data_addr(texwest_img.img, &texwest_img.bits_per_pixel, &texwest_img.line_length, &texwest_img.endian);
	if(!(all.texeast_img->img = mlx_xpm_file_to_image(all.mlx->mlx_ptr, all.scene->tex_east_file, &width, &height)))
		ft_error(ERR_CODE_3);
	all.texeast_img->addr = mlx_get_data_addr(texeast_img.img, &texeast_img.bits_per_pixel, &texeast_img.line_length, &texeast_img.endian);
	all.sprite_img->img = mlx_xpm_file_to_image(all.mlx->mlx_ptr, all.scene->sprite_file, &width, &height);
	all.sprite_img->addr = mlx_get_data_addr(sprite_img.img, &sprite_img.bits_per_pixel, &sprite_img.line_length, &sprite_img.endian);

	//check_screen_size(all);
	put_scene(all);
	put_sprites(all);
	if (all.flags->screenshot == 1)
		make_screenshot(all);
	else
	{
	mlx_put_image_to_window(all.mlx->mlx_ptr, all.mlx->win_ptr, all.data->img, 0, 0);
	mlx_hook(all.mlx->win_ptr, 2, 1L<<0, key_hook, &all);
	mlx_hook(all.mlx->win_ptr, 17, 1L<<0, close_func, 0);
	ft_putendl_fd("\nOpen", 1);
	mlx_loop(all.mlx->mlx_ptr);
	}
}
