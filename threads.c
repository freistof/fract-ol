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
	if ((f->y + SCREEN_H / 2) % DIVIDE == 0)
	{
		f->image = mlx_new_image(f->mlx, SCREEN_W, DIVIDE);
		f->image_string = mlx_get_data_addr(f->image, f->bpp, f->sl, f->endian);
		f->fi = 0;
	}
	f->x = SCREEN_W / 2 * -1;
}

static void				set_variables(t_fractal *f)
{
	f->i = 0;
	if (f->type == 'm' || f->type == 'b')
	{
		f->manx = (f->x + (f->addx * f->z)) / (f->z * SCREEN_W / 2);
		f->many = (f->y + (f->addy * f->z)) / (f->z * SCREEN_H / 2);
		f->new_real = f->manx;
		f->new_imag = f->many;
	}
	else
	{
		f->new_real = (f->x + (f->addx * f->z)) / (f->z * SCREEN_W / 2);
		f->new_imag = (f->y + (f->addy * f->z)) / (f->z * SCREEN_H / 2);
	}
}

void					*loops(void *input)
{
	t_fractal			*f;
	int					count;

	f = (t_fractal *)input;
	count = 0;
	while (count < DIVIDE)
	{
		start_image(f);
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
		count++;
		f->y++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->image, 0, f->thread_no * DIVIDE);
	return (NULL);
}

void					threads(t_fractal *f)
{
	pthread_t	threads[NUM_THREADS];
	t_fractal	*fractal;
	int			i;
	int			res;

	fractal = NULL;
	while (!fractal)
		fractal = malloc(sizeof(t_fractal) * NUM_THREADS);
	i = 0;
	while (i < NUM_THREADS)
	{
		f->y = SCREEN_H / 2 * -1 + (i * DIVIDE);
		fractal[i] = *(t_fractal *)f;
		fractal[i].thread_no = i;
		res = pthread_create(&threads[i], NULL, loops, &fractal[i]);
		res = pthread_join(threads[i], NULL);
		i++;
	}
	free(fractal);
}
