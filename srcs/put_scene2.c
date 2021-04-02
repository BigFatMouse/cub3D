/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_scene2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:10:22 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/15 21:28:15 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	put_west_east(t_all all, int x, int y)
{
	int color;

	if (all.var->side == 1)
	{
		if (all.var->step_y > 0)
		{
			color = my_mlx_pixel_take(all.texeast_img, all.var->tex_x,
						all.var->tex_y);
			my_mlx_pixel_put(all.data, x, y, color);
		}
		else if (all.var->step_y < 0)
		{
			color = my_mlx_pixel_take(all.texwest_img, all.var->tex_x,
						all.var->tex_y);
			my_mlx_pixel_put(all.data, x, y, color);
		}
	}
}

void	put_north_south(t_all all, int x, int y)
{
	int color;

	all.var->tex_y = (int)all.var->tex_pos & (TEX_HEIGHT - 1);
	all.var->tex_pos += all.var->step;
	if (all.var->side == 0)
	{
		if (all.var->step_x > 0)
		{
			color = my_mlx_pixel_take(all.texsouth_img, all.var->tex_x,
										all.var->tex_y);
			my_mlx_pixel_put(all.data, x, y, color);
		}
		else	if (all.var->step_x < 0)
		{
			color = my_mlx_pixel_take(all.texnorth_img,
									all.var->tex_x, all.var->tex_y);
			my_mlx_pixel_put(all.data, x, y, color);
		}
	}
	put_west_east(all, x, y);
}

void	put_scene(t_all all)
{
	int x;
	int	y;
	int color;

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
				put_north_south(all, x, y);
		}
	}
}

void	all_mlx2(t_all *all)
{
	int			width;
	int			height;

	if (!(all->texwest_img->img = mlx_xpm_file_to_image(all->mlx->mlx_ptr,
			all->scene->tex_west_file, &width, &height)))
		ft_error(ERR_CODE_3);
	all->texwest_img->addr = mlx_get_data_addr(all->texwest_img->img,
			&all->texwest_img->bits_per_pixel, &all->texwest_img->line_length,
			&all->texwest_img->endian);
	if (!(all->texeast_img->img = mlx_xpm_file_to_image(all->mlx->mlx_ptr,
			all->scene->tex_east_file, &width, &height)))
		ft_error(ERR_CODE_3);
	all->texeast_img->addr = mlx_get_data_addr(all->texeast_img->img,
			&all->texeast_img->bits_per_pixel, &all->texeast_img->line_length,
			&all->texeast_img->endian);
	if (!(all->sprite_img->img = mlx_xpm_file_to_image(all->mlx->mlx_ptr,
			all->scene->sprite_file, &width, &height)))
		ft_error(ERR_CODE_3);
	all->sprite_img->addr = mlx_get_data_addr(all->sprite_img->img,
			&all->sprite_img->bits_per_pixel, &all->sprite_img->line_length,
			&all->sprite_img->endian);
}

void	all_mlx(t_all *all)
{
	int			width;
	int			height;

	all->mlx->win_ptr = mlx_new_window(all->mlx->mlx_ptr, all->scene->i_width,
			all->scene->i_height, "cub3D");
	if (!(all->data->img = mlx_new_image(all->mlx->mlx_ptr, all->scene->i_width,
			all->scene->i_height)))
		ft_error(ERR_CODE_0);
	all->data->addr = mlx_get_data_addr(all->data->img,
			&all->data->bits_per_pixel,
			&all->data->line_length, &all->data->endian);
	if (!(all->texnorth_img->img = mlx_xpm_file_to_image(all->mlx->mlx_ptr,
			all->scene->tex_north_file, &width, &height)))
		ft_error(ERR_CODE_3);
	all->texnorth_img->addr = mlx_get_data_addr(all->texnorth_img->img,
		&all->texnorth_img->bits_per_pixel, &all->texnorth_img->line_length,
		&all->texnorth_img->endian);
	if (!(all->texsouth_img->img = mlx_xpm_file_to_image(all->mlx->mlx_ptr,
			all->scene->tex_south_file, &width, &height)))
		ft_error(ERR_CODE_3);
	all->texsouth_img->addr = mlx_get_data_addr(all->texsouth_img->img,
		&all->texsouth_img->bits_per_pixel,
		&all->texsouth_img->line_length, &all->texsouth_img->endian);
	all_mlx2(all);
}
