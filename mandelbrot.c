/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mandelbrot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fblom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/02 17:43:07 by fblom         #+#    #+#                 */
/*   Updated: 2019/05/02 17:43:07 by fblom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				mandelbrot(t_mlx mlx)
{
	int				i;
	long long		x;
	double		c;
	long long 		res;

	i = 0;
	x = 0;
	c = -1.38;
	while (i < 5)
	{
		res = x * x + c;
		x = res;
		mlx_pixel_put(mlx.mlx, mlx.win, x, 300, 0xfffafa);
		printf("%lli\n", res);
		i++;
	}
}
