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
