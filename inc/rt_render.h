/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:37:53 by teando            #+#    #+#             */
/*   Updated: 2025/05/08 13:18:14 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RENDER_H
# define RT_RENDER_H

# ifndef WIDTH
#  define WIDTH 1920 / 2
# endif
# ifndef HEIGHT
#  define HEIGHT 1080 / 2
# endif

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

/*render.c*/
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw(t_app *app);

#endif
