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
	if (key == LEFT)
		keeper->man->thex -= 10;
	if (key == RIGHT)
		keeper->man->thex += 10;
	if (key == UP)
		keeper->man->they -= 10;
	if (key == DOWN)
		keeper->man->they += 10;
	keeper->just_set_up = 0;
	keeper->just_set_down = 0;
	mandelbrot(keeper->mlx, keeper->man);
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
//	keeper->man->zoomx += (x - SCREEN_W / 2);
//	keeper->man->zoomy += (y - SCREEN_H / 2);
	if (button == SCROLL_UP && keeper->man->scale > 0)
	{
		if (!keeper->just_set_up)
		{
			keeper->man->thex = (x - SCREEN_W / 2);
			keeper->man->they = (y - SCREEN_H / 2);
		}
		keeper->just_set_up = 1;
		keeper->just_set_down = 0;
		keeper->man->scale -= 0.0001;
	}
	if (button == SCROLL_DOWN)
	{
		if (!keeper->just_set_down)
		{
			keeper->man->thex = (x - SCREEN_W / 2);
			keeper->man->they = (y - SCREEN_H / 2);
		}
		keeper->just_set_up = 0;
		keeper->just_set_down = 1;
		keeper->man->scale += 0.0001;
	}
	mlx_clear_window(keeper->mlx->mlx, keeper->mlx->win);
	mandelbrot(keeper->mlx, keeper->man);
	return (1);
}
