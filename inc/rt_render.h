/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:37:53 by teando            #+#    #+#             */
/*   Updated: 2025/05/14 10:28:46 by teando           ###   ########.fr       */
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

/*render.c*/
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);
t_vec3	get_ray_direction(t_camera *cam, int i, int j);

void	draw(t_app *app);

#endif
