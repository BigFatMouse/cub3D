/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:06:15 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/15 22:12:17 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	draw_all(t_all all)
{
	if (!(all.var->z_buffer = malloc(sizeof(double) * all.scene->i_width)))
		ft_error(ERR_CODE_0);
	if (!(all.mlx->mlx_ptr = mlx_init()))
		ft_error(ERR_CODE_0);
	if (all.flags->screenshot != 1)
		check_screen_size(all);
	all_mlx(&all);
	if (all.flags->screenshot == 1)
	{
		put_scene(all);
		put_sprites(all);
		make_screenshot(all);
		ft_putendl_fd("\nImage saved", 1);
	}
	else
	{
		put_scene(all);
		put_sprites(all);
		mlx_put_image_to_window(all.mlx->mlx_ptr, all.mlx->win_ptr,
			all.data->img, 0, 0);
		mlx_hook(all.mlx->win_ptr, 2, 1L << 0, key_hook, &all);
		mlx_hook(all.mlx->win_ptr, 17, 1L << 0, close_func, 0);
		ft_putendl_fd("\nOpen", 1);
		mlx_loop(all.mlx->mlx_ptr);
	}
}

int		main(int argc, char **argv)
{
	t_all		all;
	t_mlx		mlx;
	t_data		data;

	ft_bzero(&all, sizeof(t_all));
	all.mlx = &mlx;
	all.data = &data;
	all.texnorth_img = malloc(sizeof(t_data));
	all.texsouth_img = malloc(sizeof(t_data));
	all.texwest_img = malloc(sizeof(t_data));
	all.texeast_img = malloc(sizeof(t_data));
	all.sprite_img = malloc(sizeof(t_data));
	all.scene = malloc(sizeof(t_scene));
	all.var = malloc(sizeof(t_var));
	all.flags = malloc(sizeof(t_parce));
	struct_init(&all);
	parce_args(&all, argc, argv);
	draw_all(all);
}
