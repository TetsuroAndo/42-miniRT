/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:37:53 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 23:24:35 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RENDER_H
# define RT_RENDER_H

# ifndef WIDTH
#  define WIDTH 960
# endif
# ifndef HEIGHT
#  define HEIGHT 540
# endif

# include "rt_obj.h"
# include "rt_vec.h"

typedef struct s_img
{
	void	*ptr;
	char	*px;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_hit_record
{
	double	t;
	t_vec3	pos;
	t_vec3	normal;
	t_color	color;
	t_obj	*obj;
}			t_hit_record;

#endif
