/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:33:06 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/12 11:31:33 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void		filling_file_screenshot(int fd, t_all all)
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

void	pixel_file_put(int fd, t_all all)
{
  int  x;
  int  y;
  int  color;

  y = all.scene->i_height;
  while (--y >= 0)
  {
    x = 0;
    while (x < all.scene->i_width)
    {
      color = *(int*)(all.data->addr + (x * all.data->line_length 
	  	+ y * (all.data->bits_per_pixel / 8)));
      write(fd, &color, 4);
	  x++;
    }
  }
}

void			continue_screenshot(t_all all, int fd)
{
	int		size_screen;
	int		pos_pixel_data;
	int		zero;
	short	plane;

	plane = 1;
	zero = 0;
	pos_pixel_data = 54;
	size_screen = all.scene->i_width
		* all.scene->i_height * 4 + 54;
	write(fd, "BM", 2);
	write(fd, &size_screen, 4);
	write(fd, &zero, 4);			// \0 \0
	write(fd, &pos_pixel_data, 4);
	pos_pixel_data = 40;
	write(fd, &pos_pixel_data, 4);
	write(fd, &all.scene->i_width, 4);
	write(fd, &all.scene->i_height, 4);
	write(fd, &plane, 2);
	plane = 32;
	write(fd, &plane, 2);
}

void make_screenshot(t_all all)
{
	int fd;
	int size_screen;
	int zero;
	int size;

	fd = open("screen.bmp", O_CREAT | O_RDWR, 0666);
	size_screen = all.scene->i_width * all.scene->i_height * 4 + 54;
	zero = 0;
	size = all.scene->i_width * all.scene->i_height;
	if (fd < 0)
		ft_error(ERR_CODE_8);
	continue_screenshot(all, fd);
	write(fd, &zero, 4);
	write(fd, &size, 4);
	size_screen = 1000;
	write(fd, &size_screen, 4);
	write(fd, &size_screen, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
	filling_file_screenshot(fd, all);
	close(fd);
}



// void      continue_screenshot(t_all all, int fd)
// {
// 	int    size_screen;
// 	int    pos_pixel_data;
// 	int    zero;
// 	short  plane;

// 	plane = 1;
// 	zero = 0;
// 	pos_pixel_data = 54;
// 	size_screen = all.scene->i_width * all.scene->i_height * 4 + 54;
// 	write(fd, "BM", 2);
// 	write(fd, &size_screen, 4);
// 	write(fd, &zero, 4);
// 	write(fd, &pos_pixel_data, 4);
// 	pos_pixel_data = 40;
// 	write(fd, &pos_pixel_data, 4);
// 	write(fd, &all.scene->i_width, 4);
// 	write(fd, &all.scene->i_height, 4);
// 	write(fd, &plane, 2);
// 	plane = 32;
// 	write(fd, &plane, 2);
// }

// void	make_screenshot(t_all	all)
// {
// 	int fd;
// 	int size_screen;
// 	int zero;
// 	int size;

// 	fd = open("screenshot.bmp", O_CREAT | O_RDWR, 0666);
// 	size_screen = all.scene->i_width * all.scene->i_height * 4 + 54;
// 	zero = 0;
// 	size = all.scene->i_width * all.scene->i_height;
// 	if (fd < 0)
// 		ft_error(ERR_CODE_8);
// 	continue_screenshot(all, fd);
// 	write(fd, &zero, 4);
// 	write(fd, &size, 4);
// 	size_screen = 1000;
// 	write(fd, &size_screen, 4);
// 	write(fd, &size_screen, 4);
// 	write(fd, &zero, 4);
// 	write(fd, &zero, 4);
// 	pixel_file_put(fd, all);
// 	close(fd);
// }