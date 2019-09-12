/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   iterations.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fblom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/11 10:07:18 by fblom         #+#    #+#                 */
/*   Updated: 2019/09/11 10:07:18 by fblom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			*loops(void *input)
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
			if (f->type == 'm' || f->type == 'b')
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
	// pthread_exit(NULL);
	return (NULL);
}

void			threads(t_fractal *f)
{
	pthread_t	threads[NUM_THREADS];
	t_fractal	fractal[NUM_THREADS];
	int			i;
	int			res;

	i = 0;
	while (i < NUM_THREADS)
	{
		f->y = SCREEN_H / 2 * -1 + (i * DIVIDE);
		fractal[i] = *(t_fractal *)f;
		fractal[i].thread_no = i;
		res = pthread_create(&threads[i], NULL, loops, &fractal[i]);
		i++;
	}
}
