/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:11:04 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/14 20:57:57 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	parce_r(const char *line, t_all *all)
{
	if (check_params(line, "0123456789 	") || count_params(line) != 2)
		ft_error(ERR_CODE_2);
	skip_simbol(&line, ' ');
	all->scene->i_width = ft_atoi_parce(&line, all);
	skip_simbol(&line, ' ');
	all->scene->i_height = ft_atoi_parce(&line, all);
	all->flags->r++;
}

void	parce_s(char *line, t_all *all)
{
	if (*line == ' ')
	{
		++line;
		all->scene->sprite_file = ft_strtrim(line, " 	");
		all->flags->s++;
	}
	if (*line == 'O')
	{
		++line;
		all->scene->tex_south_file = ft_strtrim(line, " 	");
		all->flags->so++;
	}
}

void	parce_nwe(char *line, t_all *all)
{
	if (*line == 'N' && *(++line) == 'O')
	{
		++line;
		all->scene->tex_north_file = ft_strtrim(line, " 	");
		all->flags->no++;
	}
	else if (*line == 'W' && *(++line) == 'E')
	{
		++line;
		all->scene->tex_west_file = ft_strtrim(line, " 	");
		all->flags->we++;
	}
	else if (*line == 'E' && *(++line) == 'A')
	{
		++line;
		all->scene->tex_east_file = ft_strtrim(line, " 	");
		all->flags->ea++;
	}
	else
		ft_error(ERR_CODE_3);
}

int		parce_col(const char *line, t_all *all)
{
	int	r;
	int	g;
	int	b;

	skip_simbol(&line, ' ');
	if (check_params(line, "0123456789,") || count_params(line) != 3 || count_coma(line) != 2)
		ft_error(ERR_CODE_4);
	r = ft_atoi_move(&line);
	skip_simbol(&line, ',');
	g = ft_atoi_move(&line);
	skip_simbol(&line, ',');
	b = ft_atoi_move(&line);
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

void	parce_map(t_all *all)
{
	int		x;
	int		y;
	char	c;

	all->scene->spr_num = 0;
	y = -1;
	while (all->scene->map[++y])
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
	if (all->flags->player)
		ft_error(ERR_CODE_7);
	parce_sprite(all);
}

// int check_extension(char *name, char *ext)
// {
// 	int	len;

// 	len = ft_strlen(name);
// 	if (((ft_strnstr(name, ext, len)) != name + len - 4) || len <= 4)
// 		return(1);
// 	return (0);
// }



