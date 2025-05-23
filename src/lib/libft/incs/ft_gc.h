/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:09:10 by teando            #+#    #+#             */
/*   Updated: 2025/04/23 19:25:31 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GC_H
# define FT_GC_H

# include "ft_lst.h"
# include <stddef.h>

t_list	*ft_gc_init(void);

int		ft_gc_track(t_list *gc, void *ptr);
int		ft_gc_untrack(t_list *gc, void *ptr);

void	*ft_gc_malloc(t_list *gc, size_t size);
void	*ft_gc_calloc(t_list *gc, size_t count, size_t size);

void	ft_gc_free(t_list *gc, void **ptr);
void	ft_gc_free_data(t_list *gc);
void	ft_gc_free_nodes(t_list *gc);
void	ft_gc_clear(t_list *gc);
void	ft_gc_destroy(t_list **gc);

size_t	ft_gc_count_data(const t_list *gc);
size_t	ft_gc_free_info(const t_list *gc);
void	ft_gc_dump(const t_list *gc, int fd);

char	*str_n_cpy_gc(t_list *gc, const char *src, size_t len);

char	*ft_strdup_gc(t_list *gc, const char *s1);
char	*ft_strndup_gc(t_list *gc, const char *s1, size_t n);

char	*ft_strjoin_gc(t_list *gc, const char *s1, const char *s2);
char	*ft_strjoin3_gc(t_list *gc, const char *s1, const char *s2,
			const char *s3);

char	*ft_substr_gc(t_list *gc, const char *s, unsigned int start,
			size_t len);
char	*ft_substr_r_gc(t_list *gc, const char *s, const char sep, size_t len);
char	*ft_substr_l_gc(t_list *gc, const char *s, const char sep, size_t len);

char	*ft_strtrim_gc(t_list *gc, const char *s1, const char *set);

#endif
