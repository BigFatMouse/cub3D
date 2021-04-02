/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 13:40:35 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/15 20:39:34 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	parce_r(const char *line, t_all *all)
{
	if (check_params(line, "0123456789 ") || count_params(line) != 2)
		ft_error(ERR_CODE_2);
	skip_simbol(&line, ' ');
	all->scene->i_width = ft_atoi_parce(&line, all);
	skip_simbol(&line, ' ');
	all->scene->i_height = ft_atoi_parce(&line, all);
	if (all->scene->i_width == 0 || all->scene->i_height == 0)
		ft_error(ERR_CODE_2);
	all->flags->r++;
}

void	parce_s(char *line, t_all *all)
{
	if (*line == ' ')
	{
		++line;
		if (!(all->scene->sprite_file = ft_strtrim(line, " 	")))
			ft_error(ERR_CODE_0);
		if (check_extension(all->scene->sprite_file, ".xpm"))
			ft_error(ERR_CODE_14);
		all->flags->s++;
	}
	if (*line == 'O')
	{
		++line;
		if (!(all->scene->tex_south_file = ft_strtrim(line, " 	")))
			ft_error(ERR_CODE_0);
		if (check_extension(all->scene->tex_south_file, ".xpm"))
			ft_error(ERR_CODE_14);
		all->flags->so++;
	}
}

void	parce_ea(char *line, t_all *all)
{
	++line;
	if (!(all->scene->tex_east_file = ft_strtrim(line, " 	")))
		ft_error(ERR_CODE_0);
	if (check_extension(all->scene->tex_east_file, ".xpm"))
		ft_error(ERR_CODE_14);
	all->flags->ea++;
}

void	parce_nwe(char *line, t_all *all)
{
	if (*line == 'N' && *(++line) == 'O')
	{
		++line;
		if (!(all->scene->tex_north_file = ft_strtrim(line, " 	")))
			ft_error(ERR_CODE_0);
		if (check_extension(all->scene->tex_north_file, ".xpm"))
			ft_error(ERR_CODE_14);
		all->flags->no++;
	}
	else if (*line == 'W' && *(++line) == 'E')
	{
		++line;
		if (!(all->scene->tex_west_file = ft_strtrim(line, " 	")))
			ft_error(ERR_CODE_0);
		if (check_extension(all->scene->tex_west_file, ".xpm"))
			ft_error(ERR_CODE_14);
		all->flags->we++;
	}
	else if (*line == 'E' && *(++line) == 'A')
		parce_ea(line, all);
	else
		ft_error(ERR_CODE_3);
}
