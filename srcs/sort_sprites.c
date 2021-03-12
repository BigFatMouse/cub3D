/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:02:37 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/12 10:07:13 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	ft_swap(double *a, double *b)
{
	double	c;

	c = *b;
	*b = *a;
	*a = c;
}

void	swap_sprites(t_sprite *sprite1, t_sprite *sprite2)
{
	ft_swap(&sprite1->x, &sprite2->x);
	ft_swap(&sprite1->y, &sprite2->y);
	ft_swap(&sprite1->dist, &sprite2->dist);
}

void sort_sprites(t_all all)
{
	int	i;
	int	j;

	i = -1;
	while (++i < all.scene->spr_num)
		all.sprite[i].dist = ((all.var->pos_x - all.sprite[i].x)
		* (all.var->pos_x - all.sprite[i].x) + (all.var->pos_y
		- all.sprite[i].y) * (all.var->pos_y - all.sprite[i].y));
		
	i = 0;
	while (i < all.scene->spr_num)
	{
		j = i + 1;
		if (all.sprite[i].dist < all.sprite[j].dist)
			swap_sprites(&all.sprite[i], &all.sprite[j]);
		i++;
	}
}