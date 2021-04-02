/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 02:46:27 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/15 21:33:11 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

unsigned int	my_mlx_pixel_take(t_data *data, int x, int y)
{
	char			*addr;
	unsigned int	color;

	addr = data->addr + (y * data->line_length + x *
		(data->bits_per_pixel / 8));
	color = *(unsigned int*)addr;
	return (color);
}

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
