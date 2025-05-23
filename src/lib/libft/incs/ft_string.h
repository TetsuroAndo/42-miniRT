/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 02:17:39 by teando            #+#    #+#             */
/*   Updated: 2025/04/29 20:06:16 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t n);
void	ft_memswap(void *m1, void *m2, size_t n);

char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strcspn(const char *s, const char *reject);
char	*ft_strdup(const char *s1);
char	*ft_strdup2(const char *s1);
int		ft_strfunc(const char *s, int (*f)(int));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin2(char const *s1, char const *s2);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);
char	*ft_strjoin_free(char const *s1, char const *s2);
char	*ft_strjoin_free2(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *dst, const char *src, size_t len);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strndupex(const char *s, size_t n);
size_t	ft_strnlen(const char *s, size_t maxlen);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strpbrk(const char *s, const char *accept);
char	*ft_strrchr(const char *s, int c);
char	*ft_strrev(char *str);
size_t	ft_strspn(const char *s, const char *accept);
char	*ft_strstr(const char *big, const char *little);
char	*ft_strtok(char *restrict s, const char *restrict sep);
char	*ft_strtok_r(char *restrict s, const char *restrict sep,
			char **restrict p);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
