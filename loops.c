/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fblom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/15 10:23:13 by fblom         #+#    #+#                 */
/*   Updated: 2019/07/15 10:23:13 by fblom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void					start_image(t_fractal *f)
{
	int		*bpp;
	int		*sl;
	int		*endian;

	bpp = malloc(sizeof(int));
	sl = malloc(sizeof(int));
	endian = malloc(sizeof(int));
	f->image = mlx_new_image(f->mlx, SCREEN_W, SCREEN_H);
	f->image_string = mlx_get_data_addr(f->image, bpp, sl, endian);
	free(bpp);
	free(sl);
	free(endian);
	f->fi = 0;
}

static void				set_variables(t_fractal *f)
{
	f->i = 0;
	if (f->type == 'm' || f->type == 'b')
	{
		f->manx = (f->x + (f->addx * f->z)) / (f->z * SCREEN_W / 2);
		f->many = (f->y + (f->addy * f->z)) / (f->z * SCREEN_H / 2);
		if (f->type == 'b')
		{
			f->new_real = absolute_ld(f->manx);
			f->new_imag = absolute_ld(f->many);
		}
		else
		{
			f->new_real = f->manx;
			f->new_imag = f->many;
		}
	}
	else
	{
		f->new_real = (f->x + (f->addx * f->z)) / (f->z * SCREEN_W / 2);
		f->new_imag = (f->y + (f->addy * f->z)) / (f->z * SCREEN_H / 2);
	}
}

void					*loops(t_fractal *f)
{
	start_image(f);
	f->y = SCREEN_H / 2 * -1;
	while (f->y < SCREEN_H / 2)
	{
		f->x = SCREEN_W / 2 * -1;
		while (f->x < SCREEN_W / 2)
		{
			set_variables(f);
			while (f->i < f->it && \
			f->new_real * f->new_real + f->new_imag * f->new_imag < f->limit)
			{
				iterate(f, f->const_r, f->const_i);
				f->i++;
			}
			do_colors(f);
			f->x++;
		}
		f->y++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->image, 0, 0);
	return (NULL);
}
