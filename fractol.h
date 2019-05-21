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
# define LEFT			123
# define RIGHT			124
# define DOWN			125
# define UP				126
# define PLUS			24
# define MINUS			25

typedef struct			s_jul
{
	int					x;
	int					y;
	int					limit;
	float				const_r;
	float				const_i;
	int					*bpp;
	int					*sizeline;
	int					*endian;
}						t_jul;

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
}						t_mlx;

typedef struct 			s_man
{
	float				cx;
	float				cy;
	int					scale;
	int					limit;
	short				lp;
	float				a1;
	float				a2;
	float				b1;
	float				b2;
	int					x;
	int					y;
	float				addx;
	float				addy;
	float				ax;
	float				ay;
	int					*bpp;
	int					*sizeline;
	int					*endian;
}						t_man;

typedef struct 			s_keeper
{
	t_mlx				*mlx;
	t_man				*man;
	t_jul				*jul;
}						t_keeper;

int						deal_key(int key, t_keeper *keeper);
int						closing(void *param);
int						mouse_press(int button, int x, int y, t_keeper *keeper);
int						mouse_move(int x, int y, t_keeper *keeper);

void					open_window(t_keeper *keeper);

void					set_mandelbrot(t_man *man);
void					mandelbrot(t_mlx *mlx, t_man *man);

void					set_julia(t_jul *jul);
void					julia(t_mlx *mlx, t_jul *jul);

#endif
