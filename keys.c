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
//	x = 0;
//	y = 0;
	keeper->man->thex = SCREEN_W / 2 * -1 - x / 2;
	keeper->man->they = SCREEN_H / 2 * -1 - y / 2;
	if (button == SCROLL_UP)
		keeper->man->scale -= 0.001;
	if (button == SCROLL_DOWN)
		keeper->man->scale += 0.001;
	mlx_clear_window(keeper->mlx->mlx, keeper->mlx->win);
	open_window(keeper);
	return (1);
}
