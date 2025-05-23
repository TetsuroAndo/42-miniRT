/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:02:41 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 20:47:45 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

int	main(int ac, char **av)
{
	t_app	*app;

	app = init_app();
	if (run_parser(ac, av, app))
		exit_app(app, 1);
	init_render(app);
	setup_hooks(app);
	mlx_loop(app->mlx);
	return (0);
}
