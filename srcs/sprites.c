/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 03:41:50 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/11 16:07:04 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	ft_swap(double *a, double *b)
{
	double	c;
	
	c = *b;
	*b = *a;
	*a = c;
}

void	swap_sprites(t_sprite *sprite1, t_sprite *sprite2)
{
	ft_swap(&sprite1->x, &sprite2->x);
	ft_swap(&sprite1->y, &sprite2->y);
	ft_swap(&sprite1->dist, &sprite2->dist);
}

void	sort_sprites(t_all *all)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (i < all->scene->spr_num)
	{
		j = all->scene->spr_num - 1;
		while (j > i)
		{
			if (all->sprite[j - 1].dist < all->sprite[j].dist)
				swap_sprites(&all->sprite[j - 1], &all->sprite[j]);
			j--;
		}
		i++;
	}
}

void	sprite_distance(t_all *all)
{
	int i;
	
	i = -1;
	while (++i < all->scene->spr_num)  // calculate distance
		all->sprite[i].dist = 
		((all->var->pos_x - all->sprite[i].x) * (all->var->pos_x - all->sprite[i].x) +
		(all->var->pos_y - all->sprite[i].y) * (all->var->pos_y - all->sprite[i].y));
}

void	sprite_casting(t_all *all, int i)
{
	all->var->sprite_x = all->sprite[i].x - all->var->pos_x;
	all->var->sprite_y = all->sprite[i].y - all->var->pos_y;
	all->var->inv_det = 1.0 / (all->var->plane_x * all->var->dir_y 
			- all->var->dir_x * all->var->plane_y);
	all->var->transform_x = all->var->inv_det * (all->var->dir_y * all->var->sprite_x 
			- all->var->dir_x * all->var->sprite_y);
	all->var->transform_y = all->var->inv_det * (-all->var->plane_y * all->var->sprite_x 
			+ all->var->plane_x * all->var->sprite_y);
	all->var->sprite_screen_x = (int)((all->scene->i_width / 2) 
			* (1 + all->var->transform_x / all->var->transform_y));
	all->var->sprite_heght = abs((int)(all->scene->i_height 
			/ all->var->transform_y * all->var->asp_ratio));
	all->var->draw_start_y = -all->var->sprite_heght / 2 + all->scene->i_height / 2;
	if(all->var->draw_start_y < 0)
		all->var->draw_start_y = 0;
	all->var->draw_end_y = all->var->sprite_heght / 2 + all->scene->i_height / 2;
	if(all->var->draw_end_y >= all->scene->i_height)
		all->var->draw_end_y = all->scene->i_height - 1;
	all->var->sprite_width = abs((int)(all->scene->i_height 
			/ all->var->transform_y * all->var->asp_ratio));
	all->var->draw_start_x = -all->var->sprite_width / 2 + all->var->sprite_screen_x;
	if(all->var->draw_start_x < 0) all->var->draw_start_x = 0;
		all->var->draw_end_x = all->var->sprite_width / 2 + all->var->sprite_screen_x;
	if(all->var->draw_end_x >= all->scene->i_width)
		all->var->draw_end_x = all->scene->i_width - 1;
}

void	put_sprites(t_all all)
{
	int	i;
	
	sprite_distance(&all);
	sort_sprites(&all);
	i = -1;
	while (++i < all.scene->spr_num)
	{
		sprite_casting(&all, i);
		all.var->stripe = --all.var->draw_start_x;
		while (++all.var->stripe < all.var->draw_end_x)
		{
			int tex_x = (int)(256 * (all.var->stripe - (-all.var->sprite_width / 2
				+ all.var->sprite_screen_x)) * 64 / all.var->sprite_width) / 256;
			if (all.var->transform_y > 0 && all.var->stripe > 0 && all.var->stripe
				< all.scene->i_width && all.var->transform_y < all.var->z_buffer[all.var->stripe])
			{
				int y = all.var->draw_start_y;
				while (y < all.var->draw_end_y)
				{
					int d = (y) * 256 - all.scene->i_height * 128 + all.var->sprite_heght * 128;
					int tex_y = ((d * 64) / all.var->sprite_heght) / 256;
					int color = my_mlx_pixel_take(all.sprite_img, tex_x, tex_y);
					if (color)
						my_mlx_pixel_put(all.data, all.var->stripe, y, color);
					y++;
				}
			}
		}
	}
}