/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 20:41:49 by mhogg             #+#    #+#             */
/*   Updated: 2020/11/14 21:03:57 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*str;

	i = 0;
	len = ft_strlen(s1);
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, len + 1);
	return (str);
}
