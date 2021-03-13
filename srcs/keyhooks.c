/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 02:29:11 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/13 12:24:28 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	rotate_right(t_all all)
{
	all.var->old_dir_x = all.var->dir_x;
	all.var->dir_x = all.var->dir_x * cos(-all.var->rot_speed)
					- all.var->dir_y * sin(-all.var->rot_speed);
	all.var->dir_y = all.var->old_dir_x * sin(-all.var->rot_speed)
					+ all.var->dir_y * cos(-all.var->rot_speed);
	all.var->old_plane_x = all.var->plane_x;
	all.var->plane_x = all.var->plane_x * cos(-all.var->rot_speed)
					- all.var->plane_y * sin(-all.var->rot_speed);
	all.var->plane_y = all.var->old_plane_x * sin(-all.var->rot_speed)
					+ all.var->plane_y * cos(-all.var->rot_speed);
}

void	rotate_left(t_all all)
{
	all.var->old_dir_x = all.var->dir_x;
	all.var->dir_x = all.var->dir_x * cos(all.var->rot_speed)
					- all.var->dir_y * sin(all.var->rot_speed);
	all.var->dir_y = all.var->old_dir_x * sin(all.var->rot_speed)
					+ all.var->dir_y * cos(all.var->rot_speed);
	all.var->old_plane_x = all.var->plane_x;
	all.var->plane_x = all.var->plane_x * cos(all.var->rot_speed)
					- all.var->plane_y * sin(all.var->rot_speed);
	all.var->plane_y = all.var->old_plane_x * sin(all.var->rot_speed)
					+ all.var->plane_y * cos(all.var->rot_speed);
}

void	move_left_rigth(t_all *all, int keycode)
{
	

	if (keycode == 0)
	{
		if (all->scene->map[(int)(all->var->pos_x - all->var->dir_y
		* all->var->move_speed)][(int)(all->var->pos_y)] == '0')
			all->var->pos_x -= all->var->dir_y * all->var->move_speed;
		if (all->scene->map[(int)(all->var->pos_x)][(int)(all->var->pos_y
		+ all->var->dir_x * all->var->move_speed)] == '0')
			all->var->pos_y += all->var->dir_x * all->var->move_speed;
		printf("move scene.pos_x = %.2f, pos_y = %.2f\n", all->scene->pos_x, all->scene->pos_x);
		printf("move var.pos_x = %.2f, pos_y = %.2f\n", all->var->pos_x, all->var->pos_x);
	}
	if (keycode == 2)
	{
		if (all->scene->map[(int)(all->var->pos_x + all->var->dir_y
		* all->var->move_speed)][(int)(all->var->pos_y)] == '0')
			all->var->pos_x += all->var->dir_y * all->var->move_speed;
		if (all->scene->map[(int)(all->var->pos_x)][(int)(all->var->pos_y
		- all->var->dir_x * all->var->move_speed)] == '0')
			all->var->pos_y -= all->var->dir_x * all->var->move_speed;
		printf("move scene.pos_x = %.2f, pos_y = %.2f\n", all->scene->pos_x, all->scene->pos_x);
		printf("move var.pos_x = %.2f, pos_y = %.2f\n", all->var->pos_x, all->var->pos_x);
	}
}

void	move_back_forward(t_all *all, int keycode)
{
	if (keycode == 13)
	{
		if (all->scene->map[(int)(all->var->pos_x + all->var->dir_x *
		all->var->move_speed)][(int)(all->var->pos_y)] == '0')
			all->var->pos_x += all->var->dir_x * all->var->move_speed;
		if (all->scene->map[(int)(all->var->pos_x)][(int)(all->var->pos_y
		+ all->var->dir_y * all->var->move_speed)] == '0')
			all->var->pos_y += all->var->dir_y * all->var->move_speed;
	}
	if (keycode == 1)
	{
		if (all->scene->map[(int)(all->var->pos_x - all->var->dir_x
		* all->var->move_speed)][(int)(all->var->pos_y)] == '0')
			all->var->pos_x -= all->var->dir_x * all->var->move_speed;
		if (all->scene->map[(int)(all->var->pos_x)][(int)(all->var->pos_y
		- all->var->dir_y * all->var->move_speed)] == '0')
			all->var->pos_y -= all->var->dir_y * all->var->move_speed;
	}
}

int		key_hook(int keycode, t_all *all)
{
	if (keycode == 53)
		exit(0);
	mlx_destroy_image(all->mlx->mlx_ptr, all->data->img);
	if (keycode == 13 || keycode == 1)
		move_back_forward(all, keycode);
	if (keycode == 2 || keycode == 0)
		move_left_rigth(all, keycode);
	if (keycode == 123)
		rotate_left(*all);
	if (keycode == 124)
		rotate_right(*all);
	all->data->img = mlx_new_image(all->mlx->mlx_ptr, all->scene->i_width,
									all->scene->i_height);
	all->data->addr = mlx_get_data_addr(all->data->img,
	&all->data->bits_per_pixel, &all->data->line_length, &all->data->endian);
	put_scene(*all);
	put_sprites(*all);
	mlx_put_image_to_window(all->mlx->mlx_ptr, all->mlx->win_ptr,
									all->data->img, 0, 0);
	return (0);
}
