/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fblom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/02 15:07:09 by fblom         #+#    #+#                 */
/*   Updated: 2019/05/02 15:07:10 by fblom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx_macos/mlx.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

# include <stdio.h>

# define SCREEN_W		600
# define SCREEN_H		600

# define SCROLL_UP		5
# define SCROLL_DOWN	4
# define LEFT_CLICK		1

# define LEFT			123
# define RIGHT			124
# define DOWN			125
# define UP				126
# define PLUS			24
# define MINUS			27
# define ZERO			29
# define SPACEBAR		49

# define NUM_THREADS	4
# define DIVIDE			(SCREEN_H / NUM_THREADS)

typedef struct			s_fractal
{
	int					color_change;
	int					fi;
	int					i;
	int					x;
	int					y;
	long double			addx;
	long double			addy;
	int					limit;
	int					it;
	long double			new_real;
	long double			new_imag;
	long double			old_real;
	long double			old_imag;
	long double			const_r;
	long double			const_i;
	long double			manx;
	long double			many;
	long double			z;
	int					click;
	int					*bpp;
	int					*sl;
	int					*endian;
	void				*image;
	char				*image_string;
	void				*mlx;
	void				*win;
	char				type;
	int					thread_no;
}						t_fractal;

int						deal_key(int key, t_fractal *f);
int						closing(void *param);
int						mouse_press(int button, int x, int y, t_fractal *f);
int						mouse_move(int x, int y, t_fractal *f);

void					set_fractal(t_fractal *f, char argument);

void					threads(t_fractal *f);
void					iterate(t_fractal *f, long double x, long double y);
void					join_threads(pthread_t *threads);
void					do_colors(t_fractal *f);
void					*put_to_screen(void *args);
void					start_image(t_fractal *f);
void					mandelbrot_exc(t_fractal *f);

pthread_t				save_thread_id(pthread_t input, int which);

#endif
