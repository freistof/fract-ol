/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fblom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/02 15:06:55 by fblom         #+#    #+#                 */
/*   Updated: 2019/07/15 09:23:27 by fblom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				set_fractal(t_fractal *f, char argument)
{
	f->limit = 10;
	f->const_r = -0.835;
	f->const_i = 0.2321;
	f->z = 0.5;
	f->click = 1;
	f->addx = 0;
	f->addy = 0;
	f->it = 100;
	f->type = argument;
}

void				open_window(t_fractal *f, char argument)
{
	mlx_hook(f->win, 2, 2, deal_key, f);
	mlx_hook(f->win, 17, 17, closing, NULL);
	mlx_hook(f->win, 4, 4, mouse_press, f);
	if (argument == 'j')
		mlx_hook(f->win, 6, 6, mouse_move, f);
	loops(f);
	mlx_loop(f->mlx);
}

void				choose_fractal(char argument)
{
	t_fractal *f;

	f = NULL;
	while (!f)
		f = malloc(sizeof(t_fractal));
	f->mlx = mlx_init();
	f->win = mlx_new_window(f->mlx, SCREEN_W, SCREEN_H, "fract'ol");
	set_fractal(f, argument);
	open_window(f, argument);
}

int					main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl("Usage: ./fractol [fractol]");
		ft_putendl("-m for Mandelbrot");
		ft_putendl("-j for Julia");
		ft_putendl("-b for Burning Ship");
		return (0);
	}
	if (!ft_strequ(argv[1], "-m") && !ft_strequ(argv[1], "-j") && \
									!ft_strequ(argv[1], "-b"))
		ft_putendl("not a valid fractal");
	else
		choose_fractal(argv[1][1]);
	return (0);
}
