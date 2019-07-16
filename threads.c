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

void					join_and_cancel(pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		save_thread_id(threads[i], 1);
		i++;
	}
	save_thread_id((pthread_t)-1, -1);
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_cancel(save_thread_id(0, 0));
		i++;
	}
	save_thread_id((pthread_t)-1, -1);
}

pthread_t				save_thread_id(pthread_t input, int which)
{
	static int			i;
	static int			j;
	static pthread_t	thread_ids[NUM_THREADS];

	if (which == 1)
	{
		thread_ids[i] = input;
		i++;
		return (0);
	}
	else if (which == 0)
	{
		j++;
		return (thread_ids[j - 1]);
	}
	else
	{
		i = 0;
		j = 0;
		return (0);
	}
}

void					*put_thread_to_screen(void *args)
{
	t_fractal			*f;

	f = (t_fractal *)args;
	mlx_put_image_to_window(f->mlx, f->win, f->image, 0, f->thread_no * DIVIDE);
	return (NULL);
}

void					*make_and_put_image(void *input)
{
	t_fractal			*f;
	int					count;

	f = (t_fractal *)input;
	count = 0;
	while (count < DIVIDE)
	{
		start_image(f);
		f->x = SCREEN_W / 2 * -1;
		while (f->x < SCREEN_W / 2)
		{
			mandelbrot_exc(f);
			f->new_real = f->manx;
			f->new_imag = f->many;
			while (f->i < f->it && \
			f->new_real * f->new_real + f->new_imag * f->new_imag < f->limit)
				iterate(f, f->manx, f->many);
			do_colors(f);
			f->x++;
		}
		count++;
		f->y++;
	}
	put_thread_to_screen(f);
	pthread_exit(NULL);
	return (NULL);
}

void					mandelbrot(t_fractal *f)
{
	pthread_t			threads[NUM_THREADS];
	t_fractal			fractal[NUM_THREADS];
	int					i;

	i = 0;
	while (i < NUM_THREADS)
	{
		f->y = SCREEN_H / 2 * -1 + (i * DIVIDE);
		fractal[i] = *(t_fractal *)f;
		fractal[i].thread_no = i;
		pthread_create(&threads[i], NULL, make_and_put_image, &fractal[i]);
		i++;
	}
	join_and_cancel(threads);
}
