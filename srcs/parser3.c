/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:01:38 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/15 20:39:46 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	parce_player1(t_all *all, char c, int x, int y)
{
	all->var->pos_x = (float)y + 0.5;
	all->var->pos_y = (float)x + 0.5;
	all->flags->player++;
	all->scene->map[y][x] = '0';
	if (c == 'N')
	{
		all->var->dir_x = -1;
		all->var->dir_y = 0;
		all->var->plane_x = 0;
		all->var->plane_y = 0.66;
	}
	if (c == 'S')
	{
		all->var->dir_x = 1;
		all->var->dir_y = 0;
		all->var->plane_x = 0;
		all->var->plane_y = -0.66;
	}
}

void	parce_player(t_all *all, char c, int x, int y)
{
	parce_player1(all, c, x, y);
	if (c == 'W')
	{
		all->var->dir_x = 0;
		all->var->dir_y = -1;
		all->var->plane_x = -0.66;
		all->var->plane_y = 0;
	}
	if (c == 'E')
	{
		all->var->dir_x = 0;
		all->var->dir_y = 1;
		all->var->plane_x = 0.66;
		all->var->plane_y = 0;
	}
}

int		parce_col(const char *line, t_all *all)
{
	int	r;
	int	g;
	int	b;

	skip_simbol(&line, ' ');
	if (check_params(line, "0123456789,") || count_params(line) != 3
		|| count_coma(line) != 2)
		ft_error(ERR_CODE_4);
	r = ft_atoi_parce(&line, all);
	skip_simbol(&line, ',');
	g = ft_atoi_parce(&line, all);
	skip_simbol(&line, ',');
	b = ft_atoi_parce(&line, all);
	if (r > 255 || g > 255 || b > 255)
		ft_error(ERR_CODE_4);
	return (r << 16 | g << 8 | b);
}

void	parce_color(const char *line, t_all *all)
{
	if (*line == 'F')
	{
		all->scene->floor_color = parce_col(++line, all);
		all->flags->f++;
	}
	if (*line == 'C')
	{
		all->scene->ceill_color = parce_col(++line, all);
		all->flags->c++;
	}
}
