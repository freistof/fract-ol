/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loops.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fblom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/26 21:28:35 by fblom         #+#    #+#                 */
/*   Updated: 2019/05/26 21:28:35 by fblom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				julia(t_fractal *f)
{
	f->y = SCREEN_H / 2 * -1;
	while (f->y < SCREEN_H / 2)
	{
		f->x = SCREEN_W / 2 * -1;
		while (f->x < SCREEN_W / 2)
		{
			f->i = 0;
			f->new_real = (f->x + (f->addx * f->z)) / (f->z * SCREEN_W / 2);
			f->new_imag = (f->y + (f->addy * f->z)) / (f->z * SCREEN_H / 2);
			while (f->i < f->it && \
			f->new_real * f->new_real + f->new_imag * f->new_imag < f->limit)
				iterate(f, f->const_r, f->const_i);
			do_colors(f);
			f->x++;
		}
		f->y++;
	}
	put_to_screen(f);
}

void				mandelbrot(t_fractal *f)
{
	f->y = SCREEN_H / 2 * -1;
	while (f->y < SCREEN_H / 2)
	{
		f->x = SCREEN_W / 2 * -1;
		while (f->x < SCREEN_W / 2)
		{
			f->i = 0;
			f->manx = (f->x + (f->addx * f->z)) / (f->z * SCREEN_W / 2);
			f->many = (f->y + (f->addy * f->z)) / (f->z * SCREEN_H / 2);
			f->new_real = f->manx;
			f->new_imag = f->many;
			while (f->i < f->it && \
			f->new_real * f->new_real + f->new_imag * f->new_imag < f->limit)
				iterate(f, f->manx, f->many);
			do_colors(f);
			f->x++;
		}
		f->y++;
	}
	put_to_screen(f);	
}

void				burning_ship(t_fractal *f)
{
	f->y = SCREEN_H / 2 * -1;
	while (f->y < SCREEN_H / 2)
	{
		f->x = SCREEN_W / 2 * -1;
		while (f->x < SCREEN_W / 2)
		{
			f->i = 0;
			f->manx = (f->x + (f->addx * f->z)) / (f->z * SCREEN_W / 2);
			f->many = (f->y + (f->addy * f->z)) / (f->z * SCREEN_H / 2);
			f->new_real = f->manx;
			f->new_imag = f->many;
			while (f->i < f->it && \
			f->new_real * f->new_real + f->new_imag * f->new_imag < f->limit)
				iterate(f, f->manx, f->many);
			do_colors(f);
			f->x++;
		}
		f->y++;
	}
	put_to_screen(f);	
}
