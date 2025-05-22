/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:04:11 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 20:27:09 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

typedef enum e_status
{
	E_NONE,
	E_ALLOC,
	E_SYSTEM,
	E_MLX,
	E_SCENE,
	E_OBJ,
	E_THREAD
}	t_status;

#endif
