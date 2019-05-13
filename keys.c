/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fblom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/02 17:11:10 by fblom         #+#    #+#                 */
/*   Updated: 2019/05/02 17:11:10 by fblom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				deal_key(int key)
{
	printf("%i\n", key);
	if (key == 53)
		exit(1);
	return (0);
}

int				closing(void *param)
{
	(void)param;
	exit (0);
	return (0);
}

int				mouse_press(int button, int x, int y, t_keeper *keeper)
{
	keeper->man->thex = x - SCREEN_W / 2;
//	x = SCREEN_W / 2 * -1 - keeper->man->thex;
	keeper->man->they = y - SCREEN_H / 2;
	if (button == SCROLL_UP)
		keeper->man->scale -= 0.0005;
	if (button == SCROLL_DOWN)
		keeper->man->scale += 0.0005;
	mlx_clear_window(keeper->mlx->mlx, keeper->mlx->win);
	mandelbrot(*(keeper->mlx), *(keeper->man));
	return (1);
}
