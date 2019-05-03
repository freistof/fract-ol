/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mandelbrot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fblom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/02 17:43:07 by fblom         #+#    #+#                 */
/*   Updated: 2019/05/02 17:43:07 by fblom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				mandelbrot(t_mlx *mlx)
{
	float			cx = 0, cy = 0;
	float			scale = 0.003;
	short			limit = 4;
	short			lp;
	float			a1, b1, a2, b2;
	int				x = -640, y = -400;
	float			ax, ay;

	while (x < SCREEN_W / 2)
	{
		y = SCREEN_H / 2 * -1;
		while (y < SCREEN_H / 2)
		{
			ax = cx + x * scale;
			ay = cy + y * scale;
			a1 = ax;
			b1 = ay;
			lp = 0;
			while (lp <= 255 && a1*a1 + b1*b1 <= limit)
			{
				lp += 1;
				a2 = a1 * a1 - b1 * b1 + ax;
				b2 = 2 * a1 * b1 + ay;
				a1 = a2;
				b1 = b2;
			}
			if (lp > 255)
				lp = 0;
			mlx_pixel_put(mlx->mlx, mlx->win, x + 640, y + 400, lp);
			y++;
		}
		x++;
	}
}
