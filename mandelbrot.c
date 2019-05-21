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

void					man_iterate(t_man *man)
{
	man->lp += 1;
	man->a2 = man->a1 * man->a1 - man->b1 * man->b1 + man->ax;
	man->b2 = 2 * man->a1 * man->b1 + man->ay;
	man->a1 = man->a2;
	man->b1 = man->b2;	
}

void					free_man(t_man *man, void *image, char *image_string)
{
	free(image);
	free(image_string);
/*	free(man->bpp);
	free(man->sizeline);
	free(man->endian);*/
}

void					make_start_points(t_man *man)
{
	man->ax = man->cx + (man->x + man->addx) / man->scale;
	man->ay = man->cy + (man->y + man->addy) / man->scale;
//	printf("ax: %f\nay: %f\n", man->ax, man->ay);
/*	man->ax = 0.5;
	man->ay = -0.5;*/
	man->a1 = man->ax;
	man->b1 = man->ay;
	man->lp = 0;
}

void					mandelbrot(t_mlx *mlx, t_man *man)
{
	void				*image;
	char				*image_string;

	image = mlx_new_image(mlx->mlx, SCREEN_W, SCREEN_H);
	image_string = mlx_get_data_addr(image, man->bpp, man->sizeline, man->endian);
	man->y = SCREEN_H / 2 * -1;
	while (man->y < SCREEN_H / 2)
	{
		man->x = SCREEN_W / 2 * -1;
		while (man->x < SCREEN_W / 2)
		{
			make_start_points(man);
			while (man->lp <= 100 && man->a1 * man->a1 + man->b1 * man->b1 <= man->limit)
				man_iterate(man);
			if (man->lp < 100)
			{
				image_string[(SCREEN_W * (man->y + SCREEN_H / 2) + (man->x + SCREEN_W / 2)) * 4] = man->lp * 2;
				image_string[((SCREEN_W * (man->y + SCREEN_H / 2) + (man->x + SCREEN_W / 2)) * 4) + 1] = man->lp * 5;
				image_string[((SCREEN_W * (man->y + SCREEN_H / 2) + (man->x + SCREEN_W / 2)) * 4) + 1] = man->lp;
			}
			man->x++;
		}
		man->y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, image, 0, 0);
//	free_man(man, image, image_string);
}

void				set_mandelbrot(t_man *man)
{
	man->cx = 0;
	man->cy = 0;
	man->scale = 200;
	man->limit = 4;
	man->lp = 0;
	man->addx = -100;
	man->addy = 0;
	man->x = SCREEN_W / 2 * -1;
	man->y = SCREEN_H / 2 * -1;
	man->bpp = malloc(sizeof(int));
	man->sizeline = malloc(sizeof(int));
	man->endian = malloc(sizeof(int));
}
