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
*/

void				julia(t_mlx *mlx, t_jul *jul)
{
	void			*image;
	char			*image_string;

	int				color;
	float			const_r = 0; // must be defined by mouse movements
	float			const_i = 0; // must be defined by mouse movements
	float			zoom;
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
			new_real = 0; // ?
			new_imag = 0; // ?
			while (color < 100)
			{
				old_real = new_real;
				old_imag = new_imag;
				new_real = old_real * old_real - old_imag * old_imag + const_r;
				new_imag = 2 * old_real * old_imag + const_i;
				color++;
			}
			jul->x++;
		}
		jul->y++;
	}
}

void				set_julia(t_jul *jul)
{
	jul->bpp = malloc(sizeof(int));
	jul->sizeline = malloc(sizeof(int));
	jul->endian = malloc(sizeof(int));
}