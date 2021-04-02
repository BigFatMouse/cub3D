/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:58:47 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/15 21:32:26 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		close_func(void)
{
	exit(0);
}

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void	struct_init(t_all *all)
{
	all->flags->r = -1;
	all->flags->c = -1;
	all->flags->f = -1;
	all->flags->s = -1;
	all->flags->no = -1;
	all->flags->so = -1;
	all->flags->we = -1;
	all->flags->ea = -1;
	all->flags->player = -1;
	all->flags->map = -1;
	all->flags->screenshot = 0;
	all->var->move_speed = 0.3;
	all->var->rot_speed = 0.3;
}

void	check_screen_size(t_all all)
{
	int max_width;
	int max_height;

	mlx_get_screen_size(all.mlx->mlx_ptr, &max_width, &max_height);
	if (all.scene->i_width > max_width)
		all.scene->i_width = max_width;
	if (all.scene->i_height > max_height)
		all.scene->i_height = max_height;
}

int		check_extension(char *name, char *ext)
{
	int	len;

	len = ft_strlen(name);
	if (((ft_strnstr(name, ext, len)) != name + len - 4) || len <= 4)
		return (1);
	return (0);
}
