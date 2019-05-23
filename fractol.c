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

/*
** sets key and mouse hooks and starts the loop
*/

void				open_window(t_keeper *keeper)
{
	mlx_hook(keeper->mlx->win, 2, 2, deal_key, keeper);
	mlx_hook(keeper->mlx->win, 17, 17, closing, NULL);
	mlx_hook(keeper->mlx->win, 4, 4,  mouse_press, keeper);
	mlx_hook(keeper->mlx->win, 6, 6, mouse_move, keeper);
	if (keeper->man)
		mandelbrot(keeper->mlx, keeper->man);
	else if (keeper->jul)
		julia(keeper->mlx, keeper->jul);
	mlx_loop(keeper->mlx->mlx);
}

/*
** sets one struct for mandelbrot or julia
** another for burning ship
*/

void				choose_fractal(char *argument)
{
	t_keeper	*keeper = NULL;
	t_mlx		*mlx = NULL;
	t_man		*man = NULL;
	t_jul		*jul = NULL;

	keeper = malloc(sizeof(t_keeper));
	keeper->man = man;
	keeper->jul = jul;
	if (!mlx)
	{
		mlx = malloc(sizeof(t_mlx));
		keeper->mlx = mlx;
		mlx->mlx = mlx_init();
		mlx->win = mlx_new_window(keeper->mlx->mlx, SCREEN_W, SCREEN_H, "fract'ol");
	}
	if (ft_strequ("-m", argument))
	{
		man = malloc(sizeof(t_man));
		set_mandelbrot(man);		
		keeper->man = man;
	}
	if (ft_strequ("-j", argument))
	{
		jul = malloc(sizeof(t_jul));
		set_julia(jul);
		keeper->jul = jul;
	}
	open_window(keeper);
}

/*
** shows usage when no arguments are given
** 3 mandelbrots available
*/

int				main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl("Usage: ./fractol [fractol]");
		ft_putendl("-m for Mandelbrot");
		ft_putendl("-j for Julia");
		ft_putendl("-b for Burning Ship");
		return (0);
	}
	if (!ft_strequ(argv[1], "-m") && !ft_strequ(argv[1], "-j") && !ft_strequ(argv[1], "-b"))
		ft_putendl("not a valid fractal");
	else
		choose_fractal(argv[1]);
	return (0);
}
