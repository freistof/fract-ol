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

int				deal_key(int key, t_keeper *keeper)
{
	printf("%i\n", key);
	if (key == 53)
		exit(1);
	mlx_clear_window(keeper->mlx->mlx, keeper->mlx->win);
	keeper->man->x = SCREEN_W / 2 * -1;
	if (key == 123) // left
		keeper->man->thex -= 10;
	if (key == 124) // right
		keeper->man->thex += 10;
	if (key == 126) // up
		keeper->man->they -= 10;
	if (key == 125) // down
		keeper->man->they += 10;
	keeper->man->x += keeper->man->thex;
	keeper->man->y += keeper->man->they;
	mandelbrot(*(keeper->mlx), *(keeper->man));
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
	x = 0;
	y = 0;
	keeper->man->thex = 0; //SCREEN_W / 2 - x;
	keeper->man->they = 0; //SCREEN_H / 2 - y;
	keeper->man->x = SCREEN_W / 2 * -1;
	if (button == SCROLL_UP && keeper->man->scale > 0)
		keeper->man->scale -= 0.0005;
	if (button == SCROLL_DOWN)
		keeper->man->scale += 0.0005;
	mlx_clear_window(keeper->mlx->mlx, keeper->mlx->win);
	mandelbrot(*(keeper->mlx), *(keeper->man));
	return (1);
}
