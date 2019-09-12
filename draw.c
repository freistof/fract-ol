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

void			*put_to_screen(void *args)
{
	t_fractal *f;

	f = (t_fractal *)args;
	mlx_put_image_to_window(f->mlx, f->win, f->image, 0, \
		(((f->y + SCREEN_H / 2) / DIVIDE) - 1) * DIVIDE);
	return (NULL);
}

void			do_colors(t_fractal *f)
{
	if (f->i < f->it)
	{
		if (f->i < 10)
			f->image_string[f->fi] = f->i * 3;
		else
		{
			f->image_string[f->fi] = f->i;
			f->image_string[f->fi + 1] = f->i;
//			f->image_string[f->fi + 2] = f->i * 2;
		}
		// f->image_string[f->fi + 1] = f->i * 100;
	}
	else
	{
		f->image_string[f->fi] = 0;
		f->image_string[f->fi + 1] = 0;
		f->image_string[f->fi + 2] = 0;
	}
	f->fi += 4;
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
		f->new_real = (long double)absolute_ld(f->old_real * \
			f->old_real - f->old_imag * f->old_imag + f->manx);
		f->new_imag = (long double)absolute_ld(2 * f->old_real \
			* f->old_imag + f->many);
	}
	else
	{
		f->new_real = f->old_real * f->old_real - \
		f->old_imag * f->old_imag + addx;
		f->new_imag = 2 * f->old_real * f->old_imag + addy;
	}
	f->i++;
}

void			join_threads(pthread_t *threads)
{
	int i;

	i = 0;
	while (i < NUM_THREADS + 1)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
