/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 20:50:51 by mhogg             #+#    #+#             */
/*   Updated: 2021/02/21 00:01:31 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float		ft_atof_move(const char **str)
{
	int 	num1;
	int 	num2;
	float	minus;
	int		i;
	int		len;
	
	minus = 1;
	i = 1;
	num2 = 0;
	if ((**str == '-') && (*str)++)
		minus = -1;
	num1 = ft_atoi_move(str);
	if(**str == '.')
	{
		(*str)++;
		num2 = ft_atoi_move(str);
	}
	len = ft_numlen(num2, 10);
	while (len-- > 0)
		i *= 10;
	return (minus * ((float)num1 + (float)num2 / i));
}
