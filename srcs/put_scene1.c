/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_scene1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:04:40 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/15 20:06:51 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
	if (all.var->ray_dir_x < 0)
	{
		all.var->step_x = -1;
		all.var->side_distx = (all.var->pos_x - all.var->map_x)
			* all.var->delta_distx;
	}
	else
	{
		all.var->step_x = 1;
		all.var->side_distx = (all.var->map_x + 1.0 - all.var->pos_x) *
			all.var->delta_distx;
	}
	if (all.var->ray_dir_y < 0)
	{
		all.var->step_y = -1;
		all.var->side_disty = (all.var->pos_y - all.var->map_y) *
			all.var->delta_disty;
	}
	else
	{
		all.var->step_y = 1;
		all.var->side_disty = (all.var->map_y + 1.0 - all.var->pos_y) *
			all.var->delta_disty;
	}
}

void	perform_dda(t_all all, int x)
{
	while (all.var->hit == 0)
	{
		if (all.var->side_distx < all.var->side_disty)
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
		if (all.scene->map[all.var->map_x][all.var->map_y] == '1')
			all.var->hit = 1;
	}
}

void	texture_start(t_all all)
{
	double	wall_x;

	if (all.var->side == 0)
		wall_x = all.var->pos_y + all.var->perp_wall_dist * all.var->ray_dir_y;
	else
		wall_x = all.var->pos_x + all.var->perp_wall_dist * all.var->ray_dir_x;
	wall_x -= floor((wall_x));
	all.var->tex_x = (int)(wall_x * (double)(TEX_WIDTH));
	if (all.var->side == 0 && all.var->ray_dir_x > 0)
		all.var->tex_x = TEX_WIDTH - all.var->tex_x - 1;
	if (all.var->side == 1 && all.var->ray_dir_y < 0)
		all.var->tex_x = TEX_WIDTH - all.var->tex_x - 1;
	all.var->step = 1.0 * TEX_HEIGHT / all.var->line_height;
	all.var->tex_pos = (all.var->draw_start - all.scene->i_height / 2 +
		all.var->line_height / 2) * all.var->step;
}

void	calculate_sides(t_all all, int x)
{
	if (all.var->side == 0)
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
	if (all.var->draw_start < 0)
		all.var->draw_start = 0;
	all.var->draw_end = all.var->line_height / 2 + all.scene->i_height / 2;
	if (all.var->draw_end >= all.scene->i_height)
		all.var->draw_end = all.scene->i_height - 1;
}
