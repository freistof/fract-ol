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

void				open_window(char fractol)
{
	t_mlx			*mlx;
	t_man			*man;
	t_keeper		*keeper;

	mlx = malloc(sizeof(t_mlx));
	man = malloc(sizeof(t_man));
	keeper = malloc(sizeof(t_keeper));
	keeper->mlx = mlx;
	keeper->man = man;
	if (!fractol)
	{
		ft_putendl("not a valid fractal");
		return ;
	}
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, SCREEN_W, SCREEN_H, "fract'ol");
	mlx_hook(mlx->win, 2, 2, deal_key, NULL);
	mlx_hook(mlx->win, 17, 17, closing, NULL);
	mlx_hook(mlx->win, 4, 4,  mouse_press, keeper);
	if (fractol == 'm')
		set_mandelbrot(mlx, man);
	mlx_loop(mlx->mlx);
}

/*
** shows usage when no arguments are given
** 3 mandelbrots available
*/

int				main(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_putendl("Usage: ./fractol [fractol]");
		ft_putendl("-m for Mandelbrot");
		ft_putendl("-j for Julia");
		ft_putendl("-s for Sierpienski Gasket");
		return (0);
	}
	if (ft_strequ("-m", argv[1]))
		open_window('m');
	else if (ft_strequ("-j", argv[1]))
		open_window('j');
	else
		open_window(0);
	return (0);
}
