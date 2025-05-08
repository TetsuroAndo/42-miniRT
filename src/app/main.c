/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:02:41 by teando            #+#    #+#             */
/*   Updated: 2025/05/09 03:21:33 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

int	main(int ac, char **av)
{
	t_app	*app;

	app = init_app();
	if (run_parser(ac, av, app))
		exit_app(app, 1);
	draw(app);
	setup_hooks(app);
	mlx_loop(app->mlx);
	return (0);
}
