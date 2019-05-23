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
#define FRACTOL_H

# include "minilibx_macos/mlx.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h> // remove

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
# define MINUS			25
# define ZERO			29

typedef struct 			s_fractal
{
	int					i;
	int					x;
	int					y;
	double				addx;
	double				addy;
	int					limit;
	int					iterations;
	double				new_real;
	double				new_imag;
	double				old_real;
	double				old_imag;
	double				const_r;
	double				const_i;
	double				manx;
	double				many;
	double				zoom;
	int					click;
	int					*bpp;
	int					*sizeline;
	int					*endian;
	void				*image;
	char				*image_string;
	void				*mlx;
	void				*win;
	char				type;
}						t_fractal;

int						deal_key(int key, t_fractal *f);
int						closing(void *param);
int						mouse_press(int button, int x, int y, t_fractal *f);
int						mouse_move(int x, int y, t_fractal *f);

void					set_fractal(t_fractal *f, char argument);

void					julia(t_fractal *f);
void					mandelbrot(t_fractal *f);
void					burning_ship(t_fractal *f);

#endif
