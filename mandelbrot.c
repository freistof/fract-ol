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
	void				*image;
	char				*image_string;
	int					*bpp;
	int					*sizeline;
	int					*endian;

	
	bpp = malloc(sizeof(int));
	sizeline = malloc(sizeof(int));
	endian = malloc(sizeof(int));
	image = mlx_new_image(mlx->mlx, SCREEN_W, SCREEN_H);
	image_string = mlx_get_data_addr(image, bpp, sizeline, endian);
	man->y = SCREEN_H / 2 * -1;
	while (man->y < SCREEN_H / 2)
	{
		man->x = SCREEN_W / 2 * -1;
		while (man->x < SCREEN_W / 2)
		{
			man->ax = man->cx + (man->x + man->thex) * man->scale;
			man->ay = man->cy + (man->y + man->they) * man->scale;
			man->a1 = man->ax;
			man->b1 = man->ay;
			man->lp = 0;
			while (man->lp <= 50 && man->a1 * man->a1 + man->b1 * man->b1 <= man->limit)
			{
				man->lp += 1;
				man->a2 = man->a1 * man->a1 - man->b1 * man->b1 + man->ax;
				man->b2 = 2 * man->a1 * man->b1 + man->ay;
				man->a1 = man->a2;
				man->b1 = man->b2;
			}
			if (man->lp > 50)
				man->lp = 0;
			image_string[(SCREEN_W * (man->y + SCREEN_H / 2) + (man->x + SCREEN_W / 2)) * 4] = man->lp * 5;
			man->x++;
		}
		man->y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, image, 0, 0);
	free(image);
	free(image_string);
	free(bpp);
	free(sizeline);
	free(endian);
}

void				set_mandelbrot(t_man *man)
{
	man->cx = 0;
	man->cy = 0;
	man->scale = 0.005;
	man->limit = 1000;
	man->lp = 0;
	man->thex = -100;
	man->they = 0;
	man->x = SCREEN_W / 2 * -1;
	man->y = SCREEN_H / 2 * -1;
}
