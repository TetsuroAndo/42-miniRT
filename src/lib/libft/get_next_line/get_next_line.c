/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:10:43 by teando            #+#    #+#             */
/*   Updated: 2025/01/05 02:45:49 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	read_buf_to_newline(char **r, char **newline, char **temp,
		int fd)
{
	ssize_t	read_total;
	ssize_t	size;
	char	*buf;

	read_total = 0;
	if (*r)
		*newline = ft_strchr(*r, '\n');
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	while (!*newline)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size <= 0)
			return (free(buf), size);
		buf[size] = '\0';
		read_total += size;
		*temp = ft_strjoin2(*r, buf);
		if (!*temp)
			return (free(buf), -1);
		free(*r);
		*r = *temp;
		*newline = ft_strchr(*r + (read_total - size), '\n');
	}
	return (free(buf), read_total);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*newline;
	char		*temp;
	char		*r;
	ssize_t		read_size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	r = saved;
	newline = NULL;
	read_size = read_buf_to_newline(&r, &newline, &temp, fd);
	if (read_size == -1 && saved != r)
		return (free(saved), free(r), saved = NULL, NULL);
	if (read_size == -1 || (r && !*r))
		return (free(r), saved = NULL, NULL);
	if (read_size == 0)
		saved = NULL;
	if (newline)
	{
		saved = ft_strdup(newline + 1);
		if (!saved)
			return (free(r), NULL);
		r[newline - r + 1] = '\0';
	}
	return (r);
}
