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

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
}						t_mlx;

int						deal_key(int key);

void					mandelbrot(t_mlx *mlx);

#endif
