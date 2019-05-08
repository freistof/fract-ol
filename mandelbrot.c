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

void					mandelbrot(t_mlx *mlx, t_man *man)
{
	man->x = man->thex;
	while (man->x < SCREEN_W / 2)
	{
		man->y = man->they;
		while (man->y < SCREEN_H / 2)
		{
			man->ax = man->cx + man->x * man->scale;
			man->ay = man->cy + man->y * man->scale;
			man->a1 = man->ax;
			man->b1 = man->ay;
			man->lp = 0;
			while (man->lp <= 1000 && man->a1 * man->a1 + man->b1 * man->b1 <= man->limit)
			{
				man->lp += 1;
				man->a2 = man->a1 * man->a1 - man->b1 * man->b1 + man->ax;
				man->b2 = 2 * man->a1 * man->b1 + man->ay;
				man->a1 = man->a2;
				man->b1 = man->b2;
			}
			if (man->lp > 1000)
				man->lp = 0;
			mlx_pixel_put(mlx->mlx, mlx->win, man->x + SCREEN_W / 2, man->y + SCREEN_H / 2, man->lp);
			man->y++;
		}
		man->x++;
	}
}

void				set_mandelbrot(t_man *man)
{
	man->cx = 0;
	man->cy = 0;
	man->scale = 0.003;
	man->limit = 500;
	man->lp = 0;
	man->thex = SCREEN_W / 2 * -1;
	man->they = SCREEN_H / 2 * -1;
}
