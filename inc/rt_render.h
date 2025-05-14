/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:37:53 by teando            #+#    #+#             */
/*   Updated: 2025/05/14 12:48:11 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RENDER_H
# define RT_RENDER_H

# ifdef TEST_MODE
#  include "../test/parser/test_app.h"
# else
#  include "app.h"
# endif

# ifndef WIDTH
#  define WIDTH 1920 / 2
# endif
# ifndef HEIGHT
#  define HEIGHT 1080 / 2
# endif

typedef struct s_camera t_camera;

/* 画像バッファ */
typedef struct s_img
{
	void *ptr; /* mlx_new_image */
	char *px;  /* data addr */
	int	bpp;
	int	line_len;
	int	endian;
	int	width;
	int	height;
}		t_img;

typedef struct s_hit_record
{
	double				t;
	t_vec3				pos;
	t_vec3				normal;
	t_color				color;
	t_obj				*obj;
}						t_hit_record;

#endif
