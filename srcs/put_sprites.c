/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 03:41:50 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/12 10:07:30 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	sprite_casting1(t_all *all, int i)
{
	all->var->sprite_x = all->sprite[i].x - all->var->pos_x;
	all->var->sprite_y = all->sprite[i].y - all->var->pos_y;
	all->var->inv_det = 1.0 / (all->var->plane_x * all->var->dir_y
			- all->var->dir_x * all->var->plane_y);
	all->var->transform_x = all->var->inv_det * (all->var->dir_y
	* all->var->sprite_x - all->var->dir_x * all->var->sprite_y);
	all->var->transform_y = all->var->inv_det * (-all->var->plane_y
	* all->var->sprite_x + all->var->plane_x * all->var->sprite_y);
	all->var->sprite_screen_x = (int)((all->scene->i_width / 2)
			* (1 + all->var->transform_x / all->var->transform_y));
	all->var->sprite_heght = abs((int)(all->scene->i_height
			/ all->var->transform_y * all->var->asp_ratio));
	all->var->draw_start_y = -all->var->sprite_heght / 2
			+ all->scene->i_height / 2;
}

void	sprite_casting2(t_all *all, int i)
{
	if (all->var->draw_start_y < 0)
		all->var->draw_start_y = 0;
	all->var->draw_end_y = all->var->sprite_heght / 2
			+ all->scene->i_height / 2;
	if (all->var->draw_end_y >= all->scene->i_height)
		all->var->draw_end_y = all->scene->i_height - 1;
	all->var->sprite_width = abs((int)(all->scene->i_height
			/ all->var->transform_y * all->var->asp_ratio));
	all->var->draw_start_x = -all->var->sprite_width
			/ 2 + all->var->sprite_screen_x;
	if (all->var->draw_start_x < 0)
		all->var->draw_start_x = 0;
	all->var->draw_end_x = all->var->sprite_width
		/ 2 + all->var->sprite_screen_x;
	if (all->var->draw_end_x >= all->scene->i_width)
		all->var->draw_end_x = all->scene->i_width - 1;
}

void	put_sprite_y(t_all all)
{
	int	y;
	int	color;
	int	d;

	y = all.var->draw_start_y;
	while (y < all.var->draw_end_y)
	{
		d = (y) * 256 - all.scene->i_height * 128 +
			all.var->sprite_heght * 128;
		all.var->tex_y = ((d * 64) / all.var->sprite_heght) / 256;
		color = my_mlx_pixel_take(all.sprite_img,
		all.var->tex_x, all.var->tex_y);
		if (color)
			my_mlx_pixel_put(all.data, all.var->stripe, y, color);
		y++;
	}
}

void	put_sprites(t_all all)
{
	int	i;

	sort_sprites(all);
	i = -1;
	while (++i < all.scene->spr_num)
	{
		sprite_casting1(&all, i);
		sprite_casting2(&all, i);
		all.var->stripe = --all.var->draw_start_x;
		while (++all.var->stripe < all.var->draw_end_x)
		{
			all.var->tex_x = (int)(256 * (all.var->stripe -
			(-all.var->sprite_width / 2 + all.var->sprite_screen_x))
			* 64 / all.var->sprite_width) / 256;
			if (all.var->transform_y > 0 && all.var->stripe > 0 &&
				all.var->stripe < all.scene->i_width &&
				all.var->transform_y < all.var->z_buffer[all.var->stripe])
				put_sprite_y(all);
		}
	}
}
