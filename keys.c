/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fblom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/02 17:11:10 by fblom         #+#    #+#                 */
/*   Updated: 2019/05/02 17:11:10 by fblom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			choose(t_fractal *f)
{
	if (f->type == 'j')
		julia(f);
	if (f->type == 'm')
		mandelbrot(f);
	if (f->type == 'b')
		burning_ship(f);
}

int				deal_key(int key, t_fractal *f)
{
//	printf("key: %i\n", key);
	if (key == 53)
		exit(1);
	mlx_clear_window(f->mlx, f->win);
	if (key == LEFT)
		f->addx += 10 * f->zoom / 2;
	if (key == RIGHT)
		f->addx -= 10 * f->zoom / 2;
	if (key == UP)
		f->addy += 10 * f->zoom / 2;
	if (key == DOWN)
		f->addy -= 10 * f->zoom / 2;
	if (key == PLUS && f->iterations < 500)
		f->iterations += 100;
	if (key == MINUS && f->iterations > 100)
		f->iterations -= 100;
	if (key == ZERO)
		set_fractal(f, f->type);
	choose(f);
	return (0);
}

int				closing(void *param)
{
	(void)param;
	exit (0);
	return (0);
}


int				mouse_move(int x, int y, t_fractal *f)
{
	if (x > 0 && x < SCREEN_W && y > 0 && y < SCREEN_H && f->click)
	{
		f->const_r = 0.95 * y / SCREEN_W + 1.1;
		if (f->const_r > 1)
			f->const_r -= 2;
		else if (f->const_r < -1)
			f->const_r += 2;
		f->const_i = 0.95 * x / SCREEN_H + 1.8;
		if (f->const_i > 1)
			f->const_i -= 2;
		else if (f->const_i < -1)
			f->const_i += 2;
		mlx_clear_window(f->mlx, f->win);
		julia(f);
	}
	return (0);
}

int				mouse_press(int button, int x, int y, t_fractal *f)
{
	if (button == LEFT_CLICK)
	{
		if (f->click == 1)
			f->click = 0;
		else f->click = 1;
	}
	if (button == SCROLL_UP)
	{
		f->addx += (x - SCREEN_W / 2);
		f->addy += (y - SCREEN_H / 2);
	}
	if (button == SCROLL_UP)
		f->zoom *= 1.5;
	if (button == SCROLL_DOWN)
		f->zoom /= 1.5;
	mlx_clear_window(f->mlx, f->win);
	choose(f);	
	return (0);
}
