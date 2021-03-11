/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 03:41:50 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/11 10:01:08 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

// void	swap_sprites(t_all all, int i, int j)
// {
// 	float tmp;
// 	float pos;

// 	tmp = 0;
// 	pos = 0;
// 	tmp = all.sprite[j].dist;
// 	all.sprite[j].dist = all.sprite[i].dist;
// 	all.sprite[i].dist = tmp;
// 	pos = all.sprite[i].x;
// 	all.sprite[i].x = all.sprite[j].x;
// 	all.sprite[j].x = pos;
// 	pos = all.sprite[i].y;
// 	all.sprite[i].y = all.sprite[j].y;
// 	all.sprite[j].y = pos;
// }

// void	sort_sprites(t_all all)
// {
// 	int i;
// 	int j;

// 	i = -1;
	
// 	while (++i < all.scene->spr_num)
// 	{
// 		all.sprite[i].dist = ((all.var->pos_x - all.sprite[i].x) * 
// 		(all.var->pos_x - all.sprite[i].x) +
// 		(all.var->pos_y - all.sprite[i].y) * (all.var->pos_y - all.sprite[i].y));
// 		j = -1;
// 		while (++j < all.scene->spr_num)
// 			if (all.sprite[i].dist > all.sprite[j].dist)
// 				swap_sprites(all, i, j);
// 	}
// }

// void	swap(t_point *sprites, t_all *all)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (i < all->count)
// 	{
// 		j = 0;
// 		while (j < all->count - 1)
// 		{
// 			if (sprites[j].frst > sprites[j + 1].frst)
// 			{
// 				ft_swap(&sprites[j].frst, &sprites[j + 1].frst, 1);
// 				ft_swap(&sprites[j].scnd, &sprites[j + 1].scnd, 2);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	sortsprites(int *order, double *dist, t_all *all)
// {
// 	t_point	sprites[all->count];
// 	int		i;

// 	i = 0;
// 	while (i < all->count)
// 	{
// 		sprites[i].frst = dist[i];
// 		sprites[i].scnd = order[i];
// 		i++;
// 	}
// 	swap(sprites, all);
// 	i = 0;
// 	while (i < all->count)
// 	{
// 		dist[i] = sprites[all->count - i - 1].frst;
// 		order[i] = sprites[all->count - i - 1].scnd;
// 		i++;
// 	}
// }

void			bubble_position_sprite(t_all *all, int i, int j)
{
	float tmp;
	float position;

	tmp = 0;
	position = 0;
	tmp = all->sprite[j].dist;
	all->sprite[j].dist = all->sprite[i].dist;
	all->sprite[i].dist = tmp;
	position = all->sprite[i].x;
	all->sprite[i].x = all->sprite[j].x;
	all->sprite[j].x = position;
	position = all->sprite[i].y;
	all->sprite[i].y = all->sprite[j].y;
	all->sprite[j].y = position;
}

void			sort_sprites(t_all *all)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i++ < all->scene->spr_num)
	{
		while (j++ < all->scene->spr_num)
		{
			if (all->sprite[i].dist > all->sprite[j].dist)
				bubble_position_sprite(all, i, j);
		}
		j = 0;
	}
}

void	sprite_distance(t_all *all)
{
	int i;
	
	i = -1;
	while (++i < all->scene->spr_num)  // calculate distance
		all->sprite[i].dist = ((all->var->pos_x - all->sprite[i].x) * 
		(all->var->pos_x - all->sprite[i].x) +
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