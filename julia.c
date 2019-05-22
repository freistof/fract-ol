/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   julia.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fblom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/03 13:33:11 by fblom         #+#    #+#                 */
/*   Updated: 2019/05/03 13:33:11 by fblom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** znew = zold² + c
** c determines the shape the julia set takes on
*/

/*
** newRe = 1.5 * (x - w / 2) / (0.5 * zoom * w) + moveX;
** newIm = (y - h / 2) / (0.5 * zoom * h) + moveY;
** cRe = -0.7;
** cIm = 0.27015;
*/

void				julia(t_mlx *mlx, t_jul *jul)
{
	void			*image;
	char			*image_string;

	int				color;
//	float			const_r = -0.7; // must be defined by mouse movements
//	float			const_i = 0.27015; // must be defined by mouse movements
	float			new_real;
	float			new_imag;
	float			old_real;
	float			old_imag;

	image = mlx_new_image(mlx->mlx, SCREEN_W, SCREEN_H);
	image_string = mlx_get_data_addr(image, jul->bpp, jul->sizeline, jul->endian);
	jul->y = SCREEN_H / 2 * -1;
	while (jul->y < SCREEN_H / 2)
	{
		jul->x = SCREEN_W / 2 * -1;
		while (jul->x < SCREEN_W / 2)
		{
			color = 0;
			new_real = (jul->x + jul->addx) / (jul->zoom * SCREEN_W / 2);
			new_imag = (jul->y + jul->addy) / (jul->zoom * SCREEN_H / 2);
			while (color < jul->iter && new_real * new_real + new_imag * new_imag < jul->limit)
			{
				old_real = new_real;
				old_imag = new_imag;
				new_real = old_real * old_real - old_imag * old_imag + jul->const_r;
				new_imag = 2 * old_real * old_imag + jul->const_i;
				color++;
			}
			if (color < jul->iter)
			{
				image_string[(SCREEN_W * (jul->y + SCREEN_H / 2) + (jul->x + SCREEN_W / 2)) * 4] = color / 2;
				image_string[((SCREEN_W * (jul->y + SCREEN_H / 2) + (jul->x + SCREEN_W / 2)) * 4) + 2] = color / 2;
				image_string[((SCREEN_W * (jul->y + SCREEN_H / 2) + (jul->x + SCREEN_W / 2)) * 4) + 1] = color / 2;
			}
			else
			{
				image_string[(SCREEN_W * (jul->y + SCREEN_H / 2) + (jul->x + SCREEN_W / 2)) * 4] = 255 / 2;
				image_string[((SCREEN_W * (jul->y + SCREEN_H / 2) + (jul->x + SCREEN_W / 2)) * 4) + 2] = 125 / 2;
				image_string[((SCREEN_W * (jul->y + SCREEN_H / 2) + (jul->x + SCREEN_W / 2)) * 4) + 1] = 206 / 2;
			}
			jul->x++;
		}
		jul->y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, image, 0, 0);
	mlx_string_put(mlx->mlx, mlx->win, 10, 10, 0xFFFFFF, "zoom");
	mlx_string_put(mlx->mlx, mlx->win, 70, 10, 0xFFFFFF, ft_itoa(jul->zoom));
	mlx_string_put(mlx->mlx, mlx->win, 10, 25, 0xFFFFFF, "iter");
	mlx_string_put(mlx->mlx, mlx->win, 70, 25, 0xFFFFFF, ft_itoa(jul->iter));
}

void				set_julia(t_jul *jul)
{
	jul->limit = 1000;
	jul->const_r = -0.835;
	jul->const_i = -0.2321; //0.27015;
	jul->zoom = 0.5;
	jul->click = 1;
	jul->addx = 0;
	jul->addy = 0;
	jul->iter = 100;
	jul->bpp = malloc(sizeof(int));
	jul->sizeline = malloc(sizeof(int));
	jul->endian = malloc(sizeof(int));
}