/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:47:56 by teando            #+#    #+#             */
/*   Updated: 2025/04/25 15:46:40 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "app.h"

int init_app(void)
{
	t_app *app;

	app = (t_app *)ft_calloc(sizeof(t_app), 1);
	if (!app)
		exit(1);
	app->gc = xgc_init(app);
	
	return (0);
}