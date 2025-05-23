/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 03:11:59 by teando            #+#    #+#             */
/*   Updated: 2024/11/21 03:29:41 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRINGS_H
# define FT_STRINGS_H

# include <stddef.h>

void	ft_bzero(void *s, size_t n);
int		ft_strcasecmp(const char *s1, const char *s2);
int		ft_strncasecmp(const char *s1, const char *s2, size_t n);

#endif