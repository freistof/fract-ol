/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fblom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/02 15:06:55 by fblom         #+#    #+#                 */
/*   Updated: 2019/05/02 15:06:59 by fblom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			open_window(char fractol)
{
	t_mlx		mlx;

//	mlx = malloc(sizeof(t_mlx));
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1000, 1000, "fractol");
	mlx_hook(mlx.win, 2, 2, deal_key, NULL);
	if (fractol == 'm')
		mandelbrot(mlx);
	mlx_loop(mlx.mlx);
}

int				main(int argc, char **argv)
{
	char		fractol;

	if (argc < 2)
	{
		printf("Usage: ./fractol [fractol]\n");
		printf("-m for Mandelbrot\n");
		printf("-j for Julia\n");
		printf("-s for Sierpienski Gasket\n");
		return (0);
	}
	fractol = 0;
	if (ft_strequ("-m", argv[1]))
		fractol = 'm';
	open_window(fractol);
	return (0);
}
