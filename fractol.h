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

# define SCREEN_W 1280
# define SCREEN_H 800
# define SCROLL_UP 5
# define SCROLL_DOWN 4

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
}						t_mlx;

typedef struct 			s_man
{
	float				cx;
	float				cy;
	float				scale;
	short				limit;
	short				lp;
	float				a1;
	float				a2;
	float				b1;
	float				b2;
	int					x;
	int					y;
	int					thex;
	int					they;
	float				ax;
	float				ay;
}						t_man;


typedef struct 			s_keeper
{
	t_mlx				*mlx;
	t_man				*man;
}						t_keeper;

int						deal_key(int key);
int						closing(void *param);
int						mouse_press(int button, int x, int y, t_keeper *keeper);


void					open_window(t_keeper *keeper);

void					set_mandelbrot(t_man *man);
void					mandelbrot(t_mlx *mlx, t_man *man);

t_mlx					julia(t_mlx mlx);

#endif
