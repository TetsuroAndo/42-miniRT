/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fxaa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:32:52 by teando            #+#    #+#             */
/*   Updated: 2025/05/21 11:38:28 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_render.h"

/* 簡易輝度計算: 0-255 → 0-1023 にスケール (整数のみ) */
static inline int luma(uint32_t c)
{
    return ((c >> 16 & 0xFF) * 299   +      /* R * 0.299 */
            (c >>  8 & 0xFF) * 587   +      /* G * 0.587 */
            (c       & 0xFF) * 114) >> 8;   /* B * 0.114 */
}

/* 安全にピクセルを読み書きするマクロ */
#define PX(_x,_y) (*(uint32_t*)(img->px + ((_y) * img->line_len) + ((_x) * 4)))

void    apply_fxaa(t_img *img)
{
    const int w = img->width, h = img->height;
    /* 一時バッファを行単位で確保 (輝度だけ保存) */
    int *lum = malloc(sizeof(int) * w * h);
    if (!lum) return;                           /* メモリ不足なら諦める */

    /* 1st pass: 輝度算出 */
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
            lum[y * w + x] = luma(PX(x,y));

    /* 2nd pass: エッジ検出＋フィルタ */
    const int threshold = 20;                   /* 実験値: 0-255→約8% */
    for (int y = 1; y < h-1; ++y)
    {
        for (int x = 1; x < w-1; ++x)
        {
            /* 中央ピクセルの輝度は使用しないのでコメントアウト */
            /* int L = lum[y*w + x]; */
            int Lnw = lum[(y-1)*w + (x-1)];
            int Lne = lum[(y-1)*w + (x+1)];
            int Lsw = lum[(y+1)*w + (x-1)];
            int Lse = lum[(y+1)*w + (x+1)];

            /* ローカルコントラストが閾値未満ならスキップ */
            int maxL = Lnw; if (Lne>maxL) maxL=Lne; if(Lsw>maxL)maxL=Lsw; if(Lse>maxL)maxL=Lse;
            int minL = Lnw; if (Lne<minL) minL=Lne; if(Lsw<minL)minL=Lsw; if(Lse<minL)minL=Lse;
            if (maxL - minL < threshold) continue;

            /* エッジ方向推定 (簡易版) */
            float dir_x = -(float)( (Lnw + Lne) - (Lsw + Lse) );
            float dir_y =  (float)( (Lnw + Lsw) - (Lne + Lse) );
            float len = fabsf(dir_x)+fabsf(dir_y);
            if (len == 0.f) continue;
            dir_x /= len; dir_y /= len;

            /* 1/3, 2/3 オフセット位置の色を取得 (バイリニア) */
            float cx = x + dir_x * 0.333f;
            float cy = y + dir_y * 0.333f;
            int ix = (int)cx, iy = (int)cy;
            uint32_t col1 = PX(ix,iy);

            cx = x + dir_x * 0.666f;
            cy = y + dir_y * 0.666f;
            ix = (int)cx; iy = (int)cy;
            uint32_t col2 = PX(ix,iy);

            /* 近似カラー平均 */
            uint8_t r = ((PX(x,y)>>16 & 0xFF) + (col1>>16 & 0xFF) + (col2>>16 & 0xFF)) / 3;
            uint8_t g = ((PX(x,y)>> 8 & 0xFF) + (col1>> 8 & 0xFF) + (col2>> 8 & 0xFF)) / 3;
            uint8_t b = ((PX(x,y)     & 0xFF) + (col1     & 0xFF) + (col2     & 0xFF)) / 3;

            PX(x,y) = create_trgb(0,r,g,b);
        }
    }
    free(lum);
}
