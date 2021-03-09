/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:11:04 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/09 13:42:18 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_error(char *str)
{
	printf("%s\n", str);
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
	int res = 0;
	while(str[i] != '\0')
	{
		//printf("%c: %p\n", str[i], ft_strchr(check, str[i]));
		if(!ft_strchr(check, str[i]))
			res = 1;
		i++;
	}
	return (res);
}

void	parce_r(const char *line, t_all all)
{
	if(check_params(line, "0123456789 	,") || count_params(line) != 2)
		ft_error(ERR_CODE_2);
	skip_spaces(&line);
	all.scene->i_width = ft_atoi_move(&line);
	skip_spaces(&line);
	all.scene->i_height = ft_atoi_move(&line);
	all.flags->r++;
}

void	parce_tex(char *line, t_all all) //проверить, что файл существует
{
	//printf("texcount: %d", count_params(line));
	if (*line == 'S' && count_params(line) == 2)
	{
		line++;
		if (*line == ' ')
		{
			++line;
			all.scene->sprite_file = ft_strtrim(line, " 	");
			all.flags->s++;
		}
		if (*line == 'O')
		{
			++line;
			all.scene->tex_south_file = ft_strtrim(line, " 	");
			all.flags->so++;
		}
	}
	else if (*line == 'N' && *(++line) == 'O')
	{
		++line;
		all.scene->tex_north_file = ft_strtrim(line, " 	");
		all.flags->no++;
	}
	else if (*line == 'W' && *(++line) == 'E')
	{
		++line;
		all.scene->tex_west_file = ft_strtrim(line, " 	");
		all.flags->we++;
	}
	else if (*line == 'E' && *(++line) == 'A')
	{
		++line;
		all.scene->tex_east_file = ft_strtrim(line, " 	");
		all.flags->ea++;
	}
	else 
		{printf("else: %s\n", line);
		ft_error(ERR_CODE_3);
		}
}

int parce_col(const char *line, t_all all)
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

void	parce_color(const char *line, t_all all)
{
	
	if (*line == 'F')
	{
		all.scene->floor_color = parce_col(++line, all);
		all.flags->f++;
	}
	if (*line == 'C')
	{
		all.scene->ceill_color = parce_col(++line, all);
		all.flags->c++;
	}
}

void	parce_params(char **params, t_all all)
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
		else if (ft_strchr("12 ", params[i][0]))
		{
			all.scene->map = params + i;
			break;
		}
		else
			ft_error(ERR_CODE_1);
	}
}


// void	parce_map(char **params, int i, int size, t_all all)
// {
// 	int	j;
// 	int	m_height;
// 	//char **map;
	
// 	j = 0;
// 	m_height = size - i;  // посчитать размер карты - кол-во строк
// 	printf("size = %d, i = %d, m_heigth = %d\n", size, i, m_height);
//  //	all.scene->map = params + i;
	// if(!(all.scene->map = malloc((m_height + 1) * sizeof(char *))))
	// 	ft_error(ERR_CODE_0);
	// while (i < size)
	// {
	// 	all.scene->map[j] = ft_strtrim(params[i], " 	");
	// 	i++;
	// 	j++;
	// }
// 	j = -1;
// 	while (all.scene->map[++j])
// 		ft_putendl_fd(all.scene->map[j], 1);
// }

void	map_check(t_all all)
{	
	int	i;
	int	j;
	
	i = 0;
	//проверить, что нет посторонних символов
	while (all.scene->map[++i])
	{
		char c = (all.scene->map[i])[j];
		write(1, &c, 1);
	}
	
	//проверить, что нет пустых строк
	//проверить, что закрыта сверху (1 или 2 или пробел)
	//проверить, что закрыта слева (1 или 2 или пробел)
	//проверить, что закрыта справа (1 или 2 или пробел)
	//проверить, что закрыта снизу (1 или 2 или пробел)
	//проверить, что вокруг нулей нет пробелов
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

void	parcer(int fd, t_all all)  // 24 строки!
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
	parce_params(params, all);
	if(all.flags->r || all.flags->c || all.flags->f || all.flags->s || 
	all.flags->no || all.flags->so || all.flags->we || all.flags->ea)
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
}

// int		main(int argc, char **argv)
// {
// 	int		fd = open(argv[1], O_RDONLY);
// 	t_all	all;
// 	t_scene	scene;
// 	t_parce	flags;
	
// 	all.scene = &scene;
// 	all.flags = &flags;
// 	all.scene->floor_color = 1;
	
// 	struct_flags_init(&all);
// 	parcer(fd, all);
	
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
// 	//map_check(all);
// 	//char c = *(all.scene->map[0] + 12);
// 	char c;
// 	write(1, "\n", 1);
// 	while (all.scene->map[++j])
// 	{
// 		int i = -1;
// 		//c = all.scene->map[j][i];
// 		while ((c = all.scene->map[j][++i]) != '\0')
// 			write(1, &c, 1);
// 		write(1, "\n", 1);
// 	}
// 	// 	printf("%s\n", all.scene->map[j]);
// 	// printf("check_params: %d\n", check_params("640 -480", "0123456789 ,"));
// }