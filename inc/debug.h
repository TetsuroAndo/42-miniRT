/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_debug.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:03:55 by teando            #+#    #+#             */
/*   Updated: 2025/04/25 16:30:02 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DEBUG_H
# define RT_DEBUG_H

# define DEBUG_NONE 0
# define DEBUG_CORE (1 << 0)
# define DEBUG_INIT (1 << 1)
# define DEBUG_LOAD (1 << 2)
# define DEBUG_SCENE (1 << 3)
# define DEBUG_OBJ (1 << 4)
# define DEBUG_THREAD (1 << 5)
# define DEBUG_CAMERA (1 << 6)
# define DEBUG_ALL (~DEBUG_NONE)

#endif
