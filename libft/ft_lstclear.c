/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 21:43:15 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/15 21:43:16 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*nextelem;

	if (lst && del)
	{
		tmp = *lst;
		while (tmp)
		{
			nextelem = tmp->next;
			ft_lstdelone(tmp, del);
			tmp = nextelem;
		}
		*lst = NULL;
	}
}
