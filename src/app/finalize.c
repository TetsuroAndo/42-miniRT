/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:47:54 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 22:52:11 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

void	exit_errmsg(char *msg, int lnum, t_app *app)
{
	if (lnum)
		ft_dprintf(STDERR_FILENO, "line: %d error: ", lnum);
	else
		ft_putstr_fd("error: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit_app(app, EXIT_FAILURE);
}

void	exit_app(t_app *app, int code)
{
	if (app->fd > 0)
		xclose(&app->fd);
	if (app->img->ptr)
		mlx_destroy_image(app->mlx, app->img->ptr);
	if (app->img)
		free(app->img);
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	if (app->mlx)
	{
		mlx_loop_end(app->mlx);
		mlx_destroy_display(app->mlx);
		free(app->mlx);
	}
	ft_gc_destroy(&app->gc);
	free(app);
	exit(code);
}
