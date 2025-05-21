/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:27:38 by teando            #+#    #+#             */
/*   Updated: 2025/05/21 13:29:58 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_thread.h"

void spawn_workers(t_app *app, t_renderq *q, int nthreads)
{
	app->workers = xmalloc(sizeof(pthread_t) * nthreads, app);
	app->n_workers = nthreads;
	app->renderq = q;
	for (int i = 0; i < nthreads; ++i)
		pthread_create(&app->workers[i], NULL, worker_main, (void *)app);
	app->workers_ready = 1;
}
