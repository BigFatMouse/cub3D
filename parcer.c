/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:11:04 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/08 00:46:07 by mhogg            ###   ########.fr       */
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

void	parce_r(const char *line, t_all all)
{
	skip_spaces(&line);
	all.scene->i_width = ft_atoi_move(&line);
	skip_spaces(&line);
	all.scene->i_height = ft_atoi_move(&line);
	all.flags->r++;
}

void	parce_tex(char *line, t_all all) //проверить, что файл существует
{
	if (*line == 'N' && *(++line) == 'O')// && count_params(line) == 2)
	{
		//printf("params no: %d", count_params(line));
		++line;
		//skip_spaces(&line);
		//char *str = ft_strtrim(line, " ");
		all.scene->tex_north_file = ft_strtrim(line, " ");
		all.flags->no++;
	}
	if (*line == 'S')
	{
		line++;
		if (*line == ' ')
		{
			++line;
			//skip_spaces(&line);
			all.scene->sprite_file = ft_strtrim(line, " ");
			all.flags->s++;
		}
		if (*line == 'O')
		{
			++line;
			//skip_spaces(&line);
			all.scene->tex_south_file = ft_strtrim(line, " ");
			all.flags->so++;
		}
	}
	if (*line == 'W' && *(++line) == 'E') // && count_params(line) == 2)
	{
		++line;
		//skip_spaces(&line);
		all.scene->tex_west_file = ft_strtrim(line, " ");
		all.flags->we++;
	}
	if (*line == 'E' && *(++line) == 'A')// && count_params(line) == 2)
	{
		++line;
		//skip_spaces(&line);
		all.scene->tex_east_file = ft_strtrim(line, " ");
		all.flags->ea++;
	}
	
}

void	parce_color(const char *line, t_all all)
{
	int	r;
	int	g;
	int	b;
	
	if (*line == 'F') // добавить проверку на цифры
	{
		
		line++;
		skip_spaces(&line);
		r = ft_atoi_move(&line);
		//printf("r = %d ", r);
		skip_spaces(&line);
		g = ft_atoi_move(&line);
		//printf("g = %d ", g);
		skip_spaces(&line);
		b = ft_atoi_move(&line);
		//printf("b = %d ", b);
		all.scene->floor_color = r << 16 | g << 8 | b;
		all.flags->f++;
	}
	
	if (*line == 'C') // добавить проверку на цифры
	{
		line++;
		skip_spaces(&line);
		r = ft_atoi_move(&line);
		//printf("r = %d ", r);
		skip_spaces(&line);
		g = ft_atoi_move(&line);
		//printf("g = %d ", g);
		skip_spaces(&line);
		b = ft_atoi_move(&line);
		//printf("b = %d ", b);
		all.scene->ceill_color = r << 16 | g << 8 | b;
		all.flags->c++;
	}
}

// parce_params(char *line, t_all all)
// {
// 	if (*line == 'R' && count_params(line, ' ') == 3)
// 		pars_r(++line, all);
// 	if (*line == 'N' || *)
// 		pars_tex_files(line, all);
// }


// int get_map_width(char **params, int i, int size, t_scene *scene)
// {
// 	int	a;
// 	int	b;
// 	char str;
	
// 	a = 0;
// 	while (i < size)
// 	{
// 		str = ft_strtrim(params[i], ' ');  // пробелы в конце мб?
// 		if ((b = ft_strlen(str)) > a)
// 			a = b;
// 		i++;
// 	}
// 	free(str);
// 	return (a);
// }

// void	parce_map(char **params, int i, int size, t_scene *scene)
// {
// 	int	x;
// 	int	y;
	
// 	x = 0;
// 	y = 0;
	
// 	// scene->map = malloc()
// 	// while (i < size)
// 	// {
// 	// 	skip_spaces(&params[i]);
// 	// 	while(params[i][j])
// 	// 	{
// 	// 		scene->map[x][y] = params[i][j];
// 	// 		j++;
// 	// 	}
// 	// 	i++;
// 	// }
// }

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
	i = -1;
	// while (map[++i])
	// 	ft_putendl_fd(map[i], 1);
	return (params);
}

void	parcer(int fd, t_all all)  // 28 строк!
{
	char	*line = NULL;
	t_list	*head = NULL;
	char	**params;
	int		size;
	int		i = -1;

	while (get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	size = ft_lstsize(head);
	params = make_map(&head, size);
	while (++i < size)
	{
		if (params[i][0] == 'R' && count_params(params[i]) == 3)
			parce_r(++params[i], all);
		else if (ft_strchr("FC", params[i][0]) && count_params(params[i]) == 4)
			parce_color(params[i], all);
		else if (ft_strchr("NSWE", params[i][0]) && count_params(params[i]) == 2) //проверка на пробелы внутри
			parce_tex(params[i], all);
		else if (ft_strchr("12 ", params[i][0]))
			i++;
		else if (params[i][0] == '\n')
			i++;
		else
			ft_error(ERR_CODE_1);
	}
	if(all.flags->r || all.flags->c || all.flags->f || all.flags->s || 
	all.flags->no || all.flags->so || all.flags->we || all.flags->ea)
		ft_error(ERR_CODE_1);
	// printf("flag r = %d\n", all.flags->r);
	// printf("flag c = %d\n", all.flags->c);
	// printf("flag f = %d\n", all.flags->f);
	// printf("flag s = %d\n", all.flags->s);
	// printf("flag no = %d\n", all.flags->no);
	// printf("flag so = %d\n", all.flags->so);
	// printf("flag we = %d\n", all.flags->we);
	// printf("flag ea = %d\n", all.flags->ea);

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
	
// 	printf("R %d %d\n", all.scene->i_width, all.scene->i_height);
// 	printf("NO %s|\n", all.scene->tex_north_file);
// 	printf("SO %s\n", all.scene->tex_south_file);
// 	printf("WE %s\n", all.scene->tex_west_file);
// 	printf("EA %s\n", all.scene->tex_east_file);
// 	printf("sprite %s\n", all.scene->sprite_file);
	
// 	printf("floor %p\n", all.scene->floor_color);
// 	printf("ceill %p\n", all.scene->ceill_color);
// }