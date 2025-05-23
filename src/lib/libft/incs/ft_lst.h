/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:39:44 by teando            #+#    #+#             */
/*   Updated: 2025/04/23 15:12:19 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LST_H
# define FT_LST_H

# include <stddef.h>

typedef struct s_list
{
	struct s_list	*next;
	void			*data;
}					t_list;

t_list				*ft_create_elem(void *data);
t_list				*ft_list_at(t_list *begin_list, unsigned int nbr);
t_list				*ft_list_find(t_list *begin_list, void *data_ref,
						int (*cmp)(void *, void *));
void				ft_list_foreach(t_list *begin_list, void (*f)(void *));
void				ft_list_foreach_if(t_list *begin_list, void (*f)(void *),
						void *data_ref, int (*cmp)(void *, void *));
t_list				*ft_list_from_strs(char **strs);
t_list				*ft_list_last(t_list *begin_list);
void				ft_list_merge(t_list **begin_list1, t_list *begin_list2);
void				ft_list_remove_if(t_list **begin_list, void *data_ref,
						int (*cmp)(void *, void *), void (*free_fct)(void *));
void				ft_list_reverse(t_list **begin_list);
int					ft_list_size(t_list *begin_list);
void				ft_list_sort(t_list **begin_list, int (*cmp)(void *,
							void *));
char				**ft_list_to_strs(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdel_front(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);
size_t				ft_lstsize(t_list *lst);
void				ft_sorted_list_insert(t_list **begin_list, void *data,
						int (*cmp)(void *, void *));
void				ft_sorted_list_merge(t_list **begin_list1,
						t_list *begin_list2, int (*cmp)(void *, void *));

#endif