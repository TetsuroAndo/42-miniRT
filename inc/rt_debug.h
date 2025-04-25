/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_debug.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:03:55 by teando            #+#    #+#             */
/*   Updated: 2025/04/25 14:06:11 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DEBUG_H
#define RT_DEBUG_H

#include "rt_err.h"
#include "rt_debug.h"

#define DEBUG_NONE 0
#define DEBUG_CORE (1 << 0)
#define DEBUG_INIT (1 << 1)
#define DEBUG_LOAD (1 << 2)
#define DEBUG_3 (1 << 3)
#define DEBUG_4 (1 << 4)
#define DEBUG_5 (1 << 5)
#define DEBUG_6 (1 << 6)
#define DEBUG_7 (1 << 7)
#define DEBUG_ALL (~DEBUG_NONE)

#endif
