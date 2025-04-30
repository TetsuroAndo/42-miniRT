/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:47:54 by teando            #+#    #+#             */
/*   Updated: 2025/04/30 19:09:24 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "app.h"

void exit_app(t_app *app, int code)
{
	ft_gc_destroy(&app->gc);
	mlx_destroy_window(app->mlx, app->win);
	mlx_destroy_display(app->mlx);
	free(app->mlx);
	free(app->win);
	free(app);
	exit(code);
}
