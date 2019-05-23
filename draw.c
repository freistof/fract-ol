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

static void			put_to_screen(t_fractal *f)
{
	mlx_put_image_to_window(f->mlx, f->win, f->image, 0, 0);
	mlx_string_put(f->mlx, f->win, 10, 10, 0xFFFFFF, "zoom");
	mlx_string_put(f->mlx, f->win, 70, 10, 0xFFFFFF, ft_itoa(f->zoom));
	mlx_string_put(f->mlx, f->win, 10, 25, 0xFFFFFF, "iter");
	mlx_string_put(f->mlx, f->win, 70, 25, 0xFFFFFF, ft_itoa(f->iterations));	
}

/*
** sets the color of the image
*/

static void			set_image(t_fractal *f, int i)
{
	f->image_string[(SCREEN_W * (f->y + SCREEN_H / 2) + (f->x + SCREEN_W / 2)) * 4] = i * 5;
}

static long double	absolute_ld(long double x)
{
	if (x < 0)
		return (x * -1);
	return (x);
}

/*
** iterates over julia / mandelbrot
*/

static void			iterate(t_fractal *f, long double addx, long double addy)
{
	f->old_real = f->new_real;
	f->old_imag = f->new_imag;
	f->new_real = f->old_real * f->old_real - f->old_imag * f->old_imag + addx;
	f->new_imag = 2 * f->old_real * f->old_imag + addy;
	f->i++;
}

/*
** loops over pixels
*/

void				julia(t_fractal *f)
{
	f->y = SCREEN_H / 2 * -1;
	while (f->y < SCREEN_H / 2)
	{
		f->x = SCREEN_W / 2 * -1;
		while (f->x < SCREEN_W / 2)
		{
			f->i = 0;
			f->new_real = (f->x + f->addx) / (f->zoom * SCREEN_W / 2);
			f->new_imag = (f->y + f->addy) / (f->zoom * SCREEN_H / 2);
			while (f->i < f->iterations && f->new_real * f->new_real + f->new_imag * f->new_imag < f->limit)
				iterate(f, f->const_r, f->const_i);
			if (f->i < f->iterations)
				set_image(f, f->i);
			else
				f->image_string[(SCREEN_W * (f->y + SCREEN_H / 2) + (f->x + SCREEN_W / 2)) * 4] = 0;
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
			f->manx = (f->x + f->addx) / (f->zoom * SCREEN_W / 2);
			f->many = (f->y + f->addy) / (f->zoom * SCREEN_H / 2);
			f->new_real = f->manx;
			f->new_imag = f->many;
			while (f->i < f->iterations && f->new_real * f->new_real + f->new_imag * f->new_imag < f->limit)
				iterate(f, f->manx, f->many);
			if (f->i < f->iterations)
				set_image(f, f->i);
			else
				f->image_string[(SCREEN_W * (f->y + SCREEN_H / 2) + (f->x + SCREEN_W / 2)) * 4] = 0;
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
			f->manx = (f->x + f->addx) / (f->zoom * SCREEN_W / 2);
			f->many = (f->y + f->addy) / (f->zoom * SCREEN_H / 2);
			f->new_real = f->manx;
			f->new_imag = f->many;
			while (f->i < f->iterations && f->new_real * f->new_real + f->new_imag * f->new_imag < f->limit)
			{
				f->old_real = f->new_real;
				f->old_imag = f->new_imag;
				f->new_real = absolute_ld(f->old_real * f->old_real - f->old_imag * f->old_imag + f->manx);
				f->new_imag = absolute_ld(2 * f->old_real * f->old_imag + f->many);
				f->i++;
			}
			if (f->i < f->iterations)
				set_image(f, f->i);
			f->x++;
		}
		f->y++;
	}
	put_to_screen(f);	
}
