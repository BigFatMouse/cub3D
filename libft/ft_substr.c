/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:24:16 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/07 21:11:56 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (s == NULL)
		return (NULL);
	if ((int)start < ft_strlen(s))
	{
		if (!(str = malloc(len + 1)))
			return (NULL);
		while (i < len && s[start])
			str[i++] = s[start++];
	}
	else	if (!(str = malloc(1)))
		return (NULL);
	str[i] = '\0';
	return (str);
}
