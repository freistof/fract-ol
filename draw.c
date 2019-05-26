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

void			put_to_screen(t_fractal *f)
{
	mlx_put_image_to_window(f->mlx, f->win, f->image, 0, 0);
}

void			do_colors(t_fractal *f)
{
	if (f->i < f->it)
		f->image_string[((SCREEN_W * (f->y + SCREEN_H / 2) + (f->x + SCREEN_W / 2)) * 4) + 2] = f->i;
	else
		f->image_string[((SCREEN_W * (f->y + SCREEN_H / 2) + (f->x + SCREEN_W / 2)) * 4) + 2] = 0;
}

long double		absolute_ld(long double x)
{
	if (x < 0)
		return (x * -1);
	return (x);
}

/*
** iterates over julia / mandelbrot
*/

void			iterate(t_fractal *f, long double addx, long double addy)
{
	f->old_real = f->new_real;
	f->old_imag = f->new_imag;
	if (f->type == 'b')
	{
		f->new_real = (long double)absolute_ld(f->old_real * f->old_real - f->old_imag * f->old_imag + f->manx);
		f->new_imag = (long double)absolute_ld(2 * f->old_real * f->old_imag + f->many);
	}
	else
	{
		f->new_real = f->old_real * f->old_real - f->old_imag * f->old_imag + addx;
		f->new_imag = 2 * f->old_real * f->old_imag + addy;	
	}
	f->i++;
}
