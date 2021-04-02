/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:33:06 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/15 20:38:43 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	file_pixel_put(int fd, t_all all)
{
	int	i;
	int	j;
	int	color;

	i = all.scene->i_height;
	while (--i >= 0)
	{
		j = -1;
		while (++j < all.scene->i_width)
		{
			color = *(int*)(all.data->addr + (i * all.data->line_length
					+ j * (all.data->bits_per_pixel / 8)));
			write(fd, &color, 4);
		}
	}
}

void	screenshot(t_all all, int fd)
{
	int		width;
	int		pos_pixel_data;
	int		zero;
	short	plane;

	plane = 1;
	zero = 0;
	pos_pixel_data = 54;
	width = all.scene->i_width
		* all.scene->i_height * 4 + 54;
	write(fd, "BM", 2);
	write(fd, &width, 4);
	write(fd, &zero, 4);
	write(fd, &pos_pixel_data, 4);
	pos_pixel_data = 40;
	write(fd, &pos_pixel_data, 4);
	write(fd, &all.scene->i_width, 4);
	write(fd, &all.scene->i_height, 4);
	write(fd, &plane, 2);
	plane = 32;
	write(fd, &plane, 2);
}

void	make_screenshot(t_all all)
{
	int fd;
	int width;
	int zero;
	int size;

	zero = 0;
	if ((fd = open("screenshot.bmp", O_CREAT | O_RDWR, 0666)) < 0)
		ft_error(ERR_CODE_8);
	width = all.scene->i_width * all.scene->i_height * 4 + 54;
	size = all.scene->i_width * all.scene->i_height;
	screenshot(all, fd);
	write(fd, &zero, 4);
	write(fd, &size, 4);
	width = 1000;
	write(fd, &width, 4);
	write(fd, &width, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
	file_pixel_put(fd, all);
	close(fd);
}
