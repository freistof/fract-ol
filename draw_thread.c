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
#include "pthread.h" // yes?
#include "assert.h"

/*
** puts image and text to screen
*/

static void			*put_to_screen(void *args)
{
	t_fractal *f = (t_fractal *)args;
	printf("put_to_screen: y: %i\n", (((f->y + SCREEN_H / 2) / 75) - 1) * 75);
	mlx_put_image_to_window(f->mlx, f->win, f->image, 0, (((f->y + SCREEN_H / 2) / 75) - 1) * 75);

// 	mlx_string_put(f->mlx, f->win, 10, 10, 0xFFFFFF, "zoom");
/*	mlx_string_put(f->mlx, f->win, 70, 10, 0xFFFFFF, ft_itoa(f->zoom));
	mlx_string_put(f->mlx, f->win, 10, 25, 0xFFFFFF, "iter");
	mlx_string_put(f->mlx, f->win, 70, 25, 0xFFFFFF, ft_itoa(f->it));*/
	return ((void *)f);
}

static void			do_colors(t_fractal *f)
{
	int y;
	int x;

	y = (f->y + SCREEN_H / 2) / 75;
	x = f->x + SCREEN_W / 2;
	//printf("y: %i\n", y);
	//printf("x: %i\n", x);
	//printf("index: %i\n", (SCREEN_W * y + x) * 4);
/*	for (int i = 0; i < 100; i++)
		f->image_string[i] = 100;*/
	if (f->i < f->it)
		f->image_string[(SCREEN_W * y + x) * 4] = f->i;
	else
		f->image_string[(SCREEN_W * y + x) * 4] = 0;
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

/*
** loops over pixels
*/

void				julia(t_fractal *f)
{
	pthread_t	threads[8];
//	int			result;

	f->y = SCREEN_H / 2 * -1;
	while (f->y < SCREEN_H / 2)
	{
		if ((f->y + SCREEN_H / 2) % 75 == 0)
		{
			f->image = mlx_new_image(f->mlx, SCREEN_W, 75);
			f->image_string = mlx_get_data_addr(f->image, f->bpp, f->sl, f->endian);
		}
		f->x = SCREEN_W / 2 * -1;
		while (f->x < SCREEN_W / 2)
		{
			f->i = 0;
			f->new_real = (f->x + (f->addx * f->zoom)) / (f->zoom * SCREEN_W / 2);
			f->new_imag = (f->y + (f->addy * f->zoom)) / (f->zoom * SCREEN_H / 2);
			while (f->i < f->it && \
			f->new_real * f->new_real + f->new_imag * f->new_imag < f->limit)
				iterate(f, f->const_r, f->const_i);
			do_colors(f);
			f->x++;
		}
		f->y++;
		if ((f->y + SCREEN_H / 2) % 75 == 0)
			pthread_create(&threads[(f->y + SCREEN_H / 2) / 75], NULL, put_to_screen, f);
	}
//	put_to_screen(f);
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
			f->manx = (f->x + (f->addx * f->zoom)) / (f->zoom * SCREEN_W / 2);
			f->many = (f->y + (f->addy * f->zoom)) / (f->zoom * SCREEN_H / 2);
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
//	put_to_screen(f);	
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
			f->manx = (f->x + (f->addx * f->zoom)) / (f->zoom * SCREEN_W / 2);
			f->many = (f->y + (f->addy * f->zoom)) / (f->zoom * SCREEN_H / 2);
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
//	put_to_screen(f);	
}
