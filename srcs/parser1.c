/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:31:03 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/14 19:47:53 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	parce_args(t_all *all, int argc, char **argv)
{
	int	fd;

	if (argc == 2 || argc == 3)
	{
		if (argc == 3)
		{
			if (!ft_strncmp(argv[2], "--save", ft_strlen(argv[2])))
			{
				all->flags->screenshot = 1;
				ft_putendl_fd("\nImage saved", 1);
			}
			else
				ft_error(ERR_CODE_10);
		}
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			ft_error(ERR_CODE_13);
		if (check_extension(argv[1], ".cub"))
			ft_error(ERR_CODE_12);
		parcer(fd, all);
	}
	else
		ft_error(ERR_CODE_9);
}

void	parce_params(char **params, t_all *all, int size)
{
	int	i;

	i = -1;
	while (params[++i])
	{
		if (params[i][0] == 'R')
			parce_r(++params[i], all);
		else if (ft_strchr("FC", params[i][0]) && count_params(params[i]) == 4)
			parce_color(params[i], all);
		else if (params[i][0] == 'S' && count_params(params[i]) == 2)
			parce_s(++params[i], all);
		else if (ft_strchr("NWE", params[i][0]) && count_params(params[i]) == 2)
			parce_nwe(params[i], all);
		else if (params[i][0] == '\n' || params[i][0] == '\0')
			;
		else if (ft_strchr("1 ", params[i][0]))
		{
			all->scene->map = params + i;
			all->scene->m_width = size - i;
			all->flags->map++;
			printf("size: %d", all->scene->m_width);
			parce_map(all);
			break ;
		}
		else
			ft_error(ERR_CODE_1);
	}
}

void	check_flags(t_all *all)
{
	if (all->flags->r)
		ft_error(ERR_CODE_2);
	if (all->flags->c || all->flags->f)
		ft_error(ERR_CODE_4);
	if (all->flags->s)
		ft_error(ERR_CODE_4);
	if (all->flags->s || all->flags->no || all->flags->so || all->flags->we || all->flags->ea)
		ft_error(ERR_CODE_1);
	if (all->flags->map)
		ft_error(ERR_CODE_15);
}

char	**make_map(t_list **head, int size)
{
	char	**params;
	int		i;
	t_list	*tmp;

	if (!(params = malloc((size + 1) * sizeof(char *))))
		ft_error(ERR_CODE_0);
	i = -1;
	tmp = *head;
	while (tmp)
	{
		params[++i] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(head, free);
	return (params);
}

void	parcer(int fd, t_all *all)
{
	char	*line;
	t_list	*head;
	char	**params;
	int		rb;
	int		size;

	line = NULL;
	head = NULL;
	rb = get_next_line(fd, &line);
	if (rb <= 0)
		ft_error(ERR_CODE_16);
	while ((rb > 0))
	{
		ft_lstadd_back(&head, ft_lstnew(line));
		rb = get_next_line(fd, &line);
		printf("gnl%d\n", rb);
	}
	printf("gnl%d\n", rb);
	
	ft_lstadd_back(&head, ft_lstnew(line));

	size = ft_lstsize(head);
	params = make_map(&head, size);
	parce_params(params, all, size);
	ft_lstclear(&head, free);
	check_flags(all);
}
