/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xget_next_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:32:46 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/04 21:13:20 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "xlib.h"
#include <limits.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096
#endif

#ifndef MAX_FD
# define MAX_FD 1024
#endif

static char		*fill_next_line_buffer(int fd, char *left_char,
					char *read_buffer, t_app *app);
static char		*set_next_line(char *line_buffer, t_app *app);

char	*xget_next_line(int fd, t_app *app)
{
	static char	*left_char[MAX_FD];
	char		*read_buffer;
	char		*next_line;

	read_buffer = (char *)xmalloc((BUFFER_SIZE + 1) * sizeof(char), app);
	if ((fd < 0) || (BUFFER_SIZE <= 0) || (read(fd, NULL, 0) < 0))
	{
		ft_gc_free(app->gc, (void **)&left_char[fd]);
		ft_gc_free(app->gc, (void **)&read_buffer);
		left_char[fd] = NULL;
		read_buffer = NULL;
		return (NULL);
	}
	if (!read_buffer)
		return (NULL);
	next_line = fill_next_line_buffer(fd, left_char[fd], read_buffer, app);
	left_char[fd] = set_next_line(next_line, app);
	return (next_line);
}

static char	*fill_next_line_buffer(int fd, char *left_char, char *read_buffer,
		t_app *app)
{
	long int	read_return_value;
	char		*left_char_copy_tmp;

	read_return_value = 1;
	while (0 < read_return_value)
	{
		read_return_value = read(fd, read_buffer, BUFFER_SIZE);
		if (read_return_value == -1)
		{
			ft_gc_free(app->gc, (void **)&left_char);
			return (NULL);
		}
		if (read_return_value == 0)
			break ;
		read_buffer[read_return_value] = '\0';
		if (!left_char)
			left_char = xstrdup("", app);
		left_char_copy_tmp = left_char;
		left_char = ft_strjoin_gc(app->gc, left_char, read_buffer);
		ft_gc_free(app->gc, (void **)&left_char_copy_tmp);
		if (ft_strchr(read_buffer, '\n'))
			break ;
	}
	return (left_char);
}

static char	*set_next_line(char *line_buffer, t_app *app)
{
	size_t	i;
	char	*left_char;

	if (!line_buffer)
		return (NULL);
	i = 0;
	while ((line_buffer[i] != '\n') && (line_buffer[i] != '\0'))
		i++;
	if ((line_buffer[i] == '\0') || (line_buffer[1] == '\0'))
		return (NULL);
	left_char = ft_substr_gc(app->gc, line_buffer, i + 1, ft_strlen(line_buffer)
			- i);
	if (!left_char)
		return (NULL);
	if (*left_char == '\0')
	{
		ft_gc_free(app->gc, (void **)&left_char);
		return (NULL);
	}
	line_buffer[i + 1] = '\0';
	return (left_char);
}

/*

#include "app.h"
#include <fcntl.h>
#include <stdio.h>

static t_app	*init_test_app(void)
{
	t_app	*app;

	app = (t_app *)malloc(sizeof(t_app));
	if (!app)
		return (NULL);
	app->mlx = NULL;
	app->win = NULL;
	app->gc = NULL;
	app->gc = xgc_init(app);
	return (app);
}

int	main(void)
{
	t_app *app;
	char *line;
	int fd;

	app = init_test_app();
	if (!app)
		return (1);

	// テストファイルを開く
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		ft_gc_clear(app->gc);
		free(app->gc);
		free(app);
		printf("Error opening file\n");
		return (1);
	}

	// ファイルから1行ずつ読み込む
	while ((line = xget_next_line(fd, app)) != NULL)
	{
		printf("Line: %s", line);
	}

	close(fd);
	// cleanup
	ft_gc_clear(app->gc);
	free(app->gc);
	free(app);
	return (0);
}
*/