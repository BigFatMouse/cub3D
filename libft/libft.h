/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhogg <mhogg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 11:03:54 by mhogg             #+#    #+#             */
/*   Updated: 2021/03/14 14:03:36 by mhogg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					get_next_line(int fd, char **line);
int					ft_strlen (const char *str);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strchr(const char *s, int c);
size_t				ft_strcpy(char *dst, const char *src);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
int					ft_atoi_move(const char **str);
float				ft_atof_move(const char **str);
int					ft_numlen(int num, int base);
void				ft_putendl_fd(char *s, int fd);
int					ft_isdigit(int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle, size_t len);
char				*ft_strdup(const char *s1);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
								void (*del)(void *));

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4
#endif

