/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:04:11 by teando            #+#    #+#             */
/*   Updated: 2025/05/04 21:27:06 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ERR_H
# define RT_ERR_H

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
