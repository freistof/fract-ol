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
** puts image and text to screen
*/

void		put_to_screen(void *image, t_mlx *mlx, t_jul *jul)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, image, 0, 0);
	mlx_string_put(mlx->mlx, mlx->win, 10, 10, 0xFFFFFF, "zoom");
	mlx_string_put(mlx->mlx, mlx->win, 70, 10, 0xFFFFFF, ft_itoa(jul->zoom));
	mlx_string_put(mlx->mlx, mlx->win, 10, 25, 0xFFFFFF, "iter");
	mlx_string_put(mlx->mlx, mlx->win, 70, 25, 0xFFFFFF, ft_itoa(jul->iter));	
}

/*
** sets the color of the image
*/

void		set_image(char *image_string, t_jul *jul, int i)
{
	image_string[(SCREEN_W * (jul->y + SCREEN_H / 2) + (jul->x + SCREEN_W / 2)) * 4] = i * 10;
/*	image_string[((SCREEN_W * (jul->y + SCREEN_H / 2) + (jul->x + SCREEN_W / 2)) * 4) + 2] = i * 10;
	image_string[((SCREEN_W * (jul->y + SCREEN_H / 2) + (jul->x + SCREEN_W / 2)) * 4) + 1] = i * 10;*/
}

/*
** iterates over julia / mandelbrot
*/

void				julia(t_mlx *mlx, t_jul *jul)
{
	void			*image;
	char			*image_string;
	int				i;
	long double		new_real;
	long double		new_imag;
	long double		old_real;
	long double		old_imag;

	image = mlx_new_image(mlx->mlx, SCREEN_W, SCREEN_H);
	image_string = mlx_get_data_addr(image, jul->bpp, jul->sizeline, jul->endian);
	jul->y = SCREEN_H / 2 * -1;
	while (jul->y < SCREEN_H / 2)
	{
		jul->x = SCREEN_W / 2 * -1;
		while (jul->x < SCREEN_W / 2)
		{
			i = 0;
			new_real = (jul->x + jul->addx) / (jul->zoom * SCREEN_W / 2);
			new_imag = (jul->y + jul->addy) / (jul->zoom * SCREEN_H / 2);
			while (i < jul->iter && new_real * new_real + new_imag * new_imag < jul->limit)
			{
				old_real = new_real;
				old_imag = new_imag;
				new_real = /*1.5 * */old_real * old_real - old_imag * old_imag + jul->const_r;
				new_imag = 2 * old_real * old_imag + jul->const_i;
				i++;
			}
			if (i < jul->iter)
				set_image(image_string, jul, i);
			jul->x++;
		}
		jul->y++;
	}
	put_to_screen(image, mlx, jul);
}

/*
** set base values for the first time
*/

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