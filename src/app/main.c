/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:02:41 by teando            #+#    #+#             */
/*   Updated: 2025/05/05 19:44:19 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "app.h"

int main (int ac, char **av)
{
	t_app *app;

	app = init_app();
	if (run_parser(ac, av, app))
		return (exit_app(app, EXIT_FAILURE), 1);
	return (exit_app(app, EXIT_SUCCESS), 0);
}
