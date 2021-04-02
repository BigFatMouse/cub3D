/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:11:04 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/15 22:14:59 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	check_map(t_all *all, int x, int y)
{
	if (all->scene->map[y + 1][x] == ' ' ||
		all->scene->map[y - 1][x] == ' ' ||
		all->scene->map[y][x + 1] == ' ' ||
		all->scene->map[y][x - 1] == ' ' ||
		x == 0 || y == 0 ||
		all->scene->map[y][x + 1] == '\0' ||
		all->scene->map[y + 1][x] == '\0')
		ft_error(ERR_CODE_6);
}

void	parce_sprite(t_all *all)
{
	int		x;
	int		y;
	int		i;
	char	c;
	int		spr;

	y = -1;
	i = 0;
	spr = all->scene->spr_num;
	if (!(all->sprite = malloc(sizeof(t_sprite) * spr)))
		ft_error(ERR_CODE_0);
	while (all->scene->map[++y])
	{
		x = -1;
		while ((c = all->scene->map[y][++x]) != '\0')
		{
			if (c == '2')
			{
				all->sprite[i].x = (double)y + 0.5;
				all->sprite[i].y = (double)x + 0.5;
				i++;
			}
		}
	}
}

void	check_last_line(t_all *all, int y)
{
	int	x;
	int	i;

	i = 0;
	while (all->scene->map[++i])
		if (all->scene->map[i][0] == '\0' || all->scene->map[i][0] == '\n')
			break ;
	if (i + 1 < all->scene->m_width)
		ft_error(ERR_CODE_17);
	x = -1;
	if (all->flags->player)
		ft_error(ERR_CODE_7);
	while (all->scene->map[y][++x] != '\0')
	{
		if (all->scene->map[y][x] != ' ' && all->scene->map[y][x] != '1')
		{
			ft_error(ERR_CODE_6);
		}
	}
}

void	count_sprites(t_all *all)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < all->scene->m_width - 1)
	{
		if (check_params(all->scene->map[y], "012 NWSE"))
			ft_error(ERR_CODE_5);
		x = -1;
		while ((c = all->scene->map[y][++x]) != '\0')
		{
			if (c == '0' || c == '2' || c == 'N' || c == 'S'
				|| c == 'W' || c == 'E')
				check_map(all, x, y);
			if (c == '2')
				all->scene->spr_num++;
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
				parce_player(all, c, x, y);
		}
		y++;
	}
}

void	parce_map(t_all *all)
{
	int		x;
	int		y;
	char	c;

	all->flags->map++;
	all->scene->spr_num = 0;
	y = -1;
	while (++y < all->scene->m_width - 1)
	{
		if (check_params(all->scene->map[y], "012 NWSE"))
			ft_error(ERR_CODE_5);
		x = -1;
		while ((c = all->scene->map[y][++x]) != '\0')
		{
			if (c == '0' || c == '2' || c == 'N' || c == 'S'
				|| c == 'W' || c == 'E')
				check_map(all, x, y);
			if (c == '2')
				all->scene->spr_num++;
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
				parce_player(all, c, x, y);
		}
	}
	check_last_line(all, y);
	parce_sprite(all);
}
