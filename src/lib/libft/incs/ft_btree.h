/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 08:28:26 by teando            #+#    #+#             */
/*   Updated: 2025/04/29 20:06:45 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BTREE_H
# define FT_BTREE_H
# include <stddef.h>
# include <stdlib.h>

typedef struct s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}					t_btree;

typedef struct s_queue
{
	t_btree			*node;
	int				level;
	struct s_queue	*next;
}					t_queue;

t_btree				*ftx_btree_create_node(void *item, void *sys_info,
						void (*sys_exit)(void *));
void				ft_btree_clear(t_btree **root, void (*del)(void *));
void				ft_btree_del_node(t_btree *node, void (*del)(void *));
t_btree				*ft_btree_create_node(void *item);
void				ft_btree_apply_prefix(t_btree *root,
						void (*applyf)(void *));
void				ft_btree_apply_infix(t_btree *root, void (*applyf)(void *));
void				ft_btree_apply_suffix(t_btree *root,
						void (*applyf)(void *));
void				ft_btree_insert_data(t_btree **root, void *item,
						int (*cmpf)(void *, void *));
void				*ft_btree_search_item(t_btree *root, void *data_ref,
						int (*cmpf)(void *, void *));
int					ft_btree_level_count(t_btree *root);
void				ft_btree_apply_by_level(t_btree *root,
						void (*applyf)(void *item, int current_level,
							int is_first_elem));

#endif