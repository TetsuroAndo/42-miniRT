/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:47:56 by teando            #+#    #+#             */
/*   Updated: 2025/05/09 03:20:49 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

t_app	*init_app(void)
{
	t_app *app;

	app = (t_app *)ft_calloc(sizeof(t_app), 1);
	if (!app)
		exit(1);
	app->gc = xgc_init(app);
	app->img = ft_calloc(sizeof(t_img), 1);
	if (!app->img)
		exit_app(app, 1);

	/* ワーカー共有状態を初期化だけしておく (生成は draw() まで遅延) */
	pthread_mutex_init(&app->rstate.lock, NULL);
	pthread_cond_init(&app->rstate.cv, NULL);
	app->rstate.task_id   = 0;
	app->rstate.spp_target = 1;
	app->workers_ready = 0;

	return (app);
}
