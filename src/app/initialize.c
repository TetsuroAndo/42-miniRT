/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:47:56 by teando            #+#    #+#             */
/*   Updated: 2025/05/08 13:33:17 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "app.h"

t_app *init_app(void)
{
	t_app *app;

	app = (t_app *)ft_calloc(sizeof(t_app), 1);
	if (!app)
		exit(1);
	app->gc = xgc_init(app);
	
	return (app);
}