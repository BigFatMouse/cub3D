/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:11:04 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/11 01:41:50 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void	skip_spaces(const char **str)
{
	while (**str == ' ' || **str == '\t' || **str == ',')
		(*str)++;
}

int	count_params(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != ' ' && s[i] != ',' && s[i] != '\t') && 
		(s[i + 1] == ' ' || s[i + 1] == ',' || s[i] == '\t' || s[i + 1] == '\0')) //что-то сделать с запятыми
			count++;
		i++;
	}
	return (count);
}

int	check_params(const char *str, const char *check) //функция, которая проверяет, что в строке содержатся только символы из второй строки
{
	int	i;
	i = 0;
	
	while(str[i] != '\0')
	{
		//printf("%c: %p\n", str[i], ft_strchr(check, str[i]));
		if(!ft_strchr(check, str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	parce_r(const char *line, t_all *all)
{
	if(check_params(line, "0123456789 	,") || count_params(line) != 2)
		ft_error(ERR_CODE_2);
	skip_spaces(&line);
	all->scene->i_width = ft_atoi_move(&line);
	skip_spaces(&line);
	all->scene->i_height = ft_atoi_move(&line);
	all->flags->r++;
}

void	parce_tex(char *line, t_all *all) //проверить, что файл существует
{
	//printf("texcount: %d", count_params(line));
	if (*line == 'S' && count_params(line) == 2)
	{
		line++;
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
	else if (*line == 'N' && *(++line) == 'O')
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
		{printf("else: %s\n", line);
		ft_error(ERR_CODE_3);
		}
}

int parce_col(const char *line, t_all *all)
{
	int	r;
	int	g;
	int	b;
	
	//if(!check_params ==)
	skip_spaces(&line);
	r = ft_atoi_move(&line);
	skip_spaces(&line);
	g = ft_atoi_move(&line);
	skip_spaces(&line);
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

void	parce_player(t_all *all, char c, int x, int y)
{
	all->scene->pos_x = (float)x + 0.5;
	all->scene->pos_y = (float)y + 0.5;
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
		all->scene->map[y][x - 1] == ' ' ||		//проверить, что нет пробелов
		x == 0 || y == 0 || //что не первый символ в строке/столбце
		all->scene->map[y][x + 1] == '\0' ||//не последний символ в строке
		all->scene->map[y + 1][x] == '\0')	//не последний символ в столбце
		//(x + 1) == all->scene->m_width) 
		ft_error(ERR_CODE_6);
}

void	parce_sprite(t_all *all)
{
	int y = -1;
	int i = 0;
	int spr = all->scene->spr_num;
	char	c;
	if (!(all->sprite = malloc(sizeof(t_sprite) * spr)))
		ft_error(ERR_CODE_1);
	while (all->scene->map[++y])
	{
		int x = -1;
		while ((c = all->scene->map[y][++x]) != '\0')
		{
			if (c == '2')
			{
				printf("x,y: %d,%d\n", x, y);
				all->sprite[i].x = (double)y + 0.5;
				all->sprite[i].y = (double)x + 0.5;
				printf("x%d,y%d: %.2f,%.2f\n", i, i, all->sprite[i].x, all->sprite[i].y);
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
		if (check_params(all->scene->map[y], "012 NWSE")) //проверить, что нет посторонних символов
			ft_error(ERR_CODE_5);
		int x = -1;
		while ((c = all->scene->map[y][++x]) != '\0')
		{
			write(1, &c, 1);
			if (c == '0' || c == '2' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
				check_map(all, x, y);
			if (c == '2')
				all->scene->spr_num++;
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
				parce_player(all, c, x, y);
		}
		write(1, "\n", 1);
	}
	if (all->flags->player)
		ft_error(ERR_CODE_7);
	parce_sprite(all);
	printf("sprites = %d\n", all->scene->spr_num);
}

void	parce_params(char **params, t_all *all, int size)
{
	int		i;
	
	i = -1;
	while (params[++i])
	{
		if (params[i][0] == 'R')
			parce_r(++params[i], all);
		else if (ft_strchr("FC", params[i][0]) && count_params(params[i]) == 4)
			parce_color(params[i], all);
		else if (ft_strchr("NSWE", params[i][0]) && count_params(params[i]) == 2)
			parce_tex(params[i], all);
		else if (params[i][0] == '\n' || params[i][0] == '\0')
			;
		else if (ft_strchr("1 ", params[i][0]))
		{
			all->scene->map = params + i;
			all->scene->m_width = size - i;
			//printf("size_all = %d, size_map = %d\n", size, all->scene->m_width);
			parce_map(all);
			break;
		}
		else
			ft_error(ERR_CODE_1);
	}
}

char	**make_map(t_list **head, int size)  //возвращает массив строк
{
	char	**params;
	int		i;
	t_list	*tmp;
	
	if(!(params = malloc((size + 1) * sizeof(char *))))
		ft_error(ERR_CODE_0);
	i = -1;
	tmp = *head;
	while (tmp)
	{
		params[++i] = tmp->content;
		tmp = tmp->next;
	}
	return (params);
}

void	parcer(int fd, t_all *all)  // 24 строки!
{
	char	*line;
	t_list	*head;
	t_list	*tmp;
	char	**params;
	int		i;

	line = NULL;
	head = NULL;
	while (get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	if(!(params = malloc((ft_lstsize(head) + 1) * sizeof(char *))))
		ft_error(ERR_CODE_0);
	i = -1;
	tmp = head;
	while (tmp)
	{
		params[++i] = tmp->content;
		tmp = tmp->next;
	}
	parce_params(params, all, ft_lstsize(head));
	if (all->flags->r || all->flags->c || all->flags->f || all->flags->s || 
	all->flags->no || all->flags->so || all->flags->we || all->flags->ea)
		ft_error(ERR_CODE_1);
}

void	struct_flags_init(t_all *all)
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
}

// int		main(int argc, char **argv)
// {
// 	int		fd = open(argv[1], O_RDONLY);
// 	t_all	all;
// 	t_scene	scene;
// 	t_parce	flags;
// 	t_var	var;
// 	t_sprite	sprite;
	
// 	all.scene = &scene;
// 	all.flags = &flags;
// 	all.var = &var;
// 	all.sprite = &sprite;
	
// 	struct_flags_init(&all);
// 	parcer(fd, &all);
	
// 	printf("params:\nR %d %d\n", all.scene->i_width, all.scene->i_height);
// 	printf("NO %s|\n", all.scene->tex_north_file);
// 	printf("SO %s\n", all.scene->tex_south_file);
// 	printf("WE %s\n", all.scene->tex_west_file);
// 	printf("EA %s\n", all.scene->tex_east_file);
// 	printf("sprite %s\n", all.scene->sprite_file);
// 	printf("floor %p\n", all.scene->floor_color);
// 	printf("ceill %p\n", all.scene->ceill_color);
// 	printf("map:\n");
// 	int j = -1;
// 	parce_map(&all);
	
// 	char c;
// 	write(1, "\n", 1);
// 	printf("parce:\n");
// 	printf("all.var->dir_x: %.2f\n", all.var->dir_x);
// 	printf("all.var->dir_y: %.2f\n", all.var->dir_y);
// 	printf("all.scene->pos_x: %.2f\n", all.scene->pos_x);
// 	printf("all.scene->pos_y: %.2f\n", all.scene->pos_y);
// 	printf("all.var->plane_x: %.2f\n", all.var->plane_x);
// 	printf("all.var->plane_y: %.2f\n", all.var->plane_y);
// 	printf("all.flags->player: %d\n", all.flags->player);
// 	int i = 1;
// 	while (i < all.scene->spr_num)
// 	{
// 		printf("sprite_x%d: %.2f\n", i, all.sprite[i].x);
// 		printf("sprite_y%d: %.2f\n", i, all.sprite[i].y);
// 		i++;
// 	}
	
// 	//printf("all.scene->spr_num: %d", spr);
// 	// while (all.scene->map[++j])
// 	// {
// 	// 	int i = -1;
// 	// 	//c = all.scene->map[j][i];
// 	// 	while ((c = all.scene->map[j][++i]) != '\0')
// 	// 		write(1, &c, 1);
// 	// 	write(1, "\n", 1);
// 	// }
// 	// 	printf("%s\n", all.scene->map[j]);
// 	// printf("check_params: %d\n", check_params("640 -480", "0123456789 ,"));
// }