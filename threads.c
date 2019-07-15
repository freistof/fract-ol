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

void				*make_and_put_image(void *input)
{
	t_fractal		*f;

	f = (t_fractal *)input;
	printf("f->fi: %i\n", f->fi);
	f->y = 0;
	while (f->y < DIVIDE)
	{
		f->x = 0;
		while (f->x < SCREEN_W)
		{
			printf("x: %i\ny: %i\n", f->x, f->y);
			mlx_pixel_put(f->mlx, f->win, f->x, f->y, 123123123);
			f->x++;
		}
		f->y++;
	}
	return (NULL);
}

void				mandelbrot(t_fractal *f)
{
	pthread_t		threads[NUM_THREADS];
	t_fractal		fractal[NUM_THREADS];
	int				i;

	i = 0;
	f->thread_no = malloc(sizeof(int) * 4);
	while (i < NUM_THREADS)
	{
		fractal[i] = *(t_fractal *)f;
		fractal[i].fi = i;
		pthread_create(&threads[i], NULL, make_and_put_image, &fractal[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
