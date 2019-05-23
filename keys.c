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
	printf("key: %i\n", key);
	if (key == 53)
		exit(1);
	if (keeper->man)
	{
		mlx_clear_window(keeper->mlx->mlx, keeper->mlx->win);
		if (key == LEFT)
			keeper->man->addx -= 10;
		if (key == RIGHT)
			keeper->man->addx += 10;
		if (key == UP)
			keeper->man->addy -= 10;
		if (key == DOWN)
			keeper->man->addy += 10;
		if (key == PLUS)
			keeper->man->iter += 100;
		if (key == MINUS)
			keeper->man->iter -= 100;
/*		if (key == D)
			switch(keeper->man->depth);*/
		mandelbrot(keeper->mlx, keeper->man);
	}
	if (keeper->jul)
	{
		mlx_clear_window(keeper->mlx->mlx, keeper->mlx->win);
		if (key == LEFT)
			keeper->jul->addx -= 10;
		if (key == RIGHT)
			keeper->jul->addx += 10;
		if (key == UP)
			keeper->jul->addy -= 10;
		if (key == DOWN)
			keeper->jul->addy += 10;
		if (key == PLUS)
			keeper->jul->iter += 100;
		if (key == MINUS)
			keeper->jul->iter -= 100;
		julia(keeper->mlx, keeper->jul);
	}
	return (0);
}

int				closing(void *param)
{
	(void)param;
	exit (0);
	return (0);
}

int				mouse_move(int x, int y, t_keeper *keeper)
{
	float fx = (float)x;
	float fy = (float)y;
	if (keeper->jul && x > 0 && x < SCREEN_W && y > 0 && y < SCREEN_H && keeper->jul->click)
	{
		keeper->jul->const_r = 0.95 * (fy/* - SCREEN_W / 2*/) / SCREEN_W + 1;
		if (keeper->jul->const_r > 1)
			keeper->jul->const_r -= 2;
		else if (keeper->jul->const_r < -1)
			keeper->jul->const_r += 2;
		keeper->jul->const_i = 0.95 * (fx/* - SCREEN_H / 2*/) / SCREEN_H + 1;
		if (keeper->jul->const_i > 1)
			keeper->jul->const_i -= 2;
		if (keeper->jul->const_i < -1)
			keeper->jul->const_i += 2;
		mlx_clear_window(keeper->mlx->mlx, keeper->mlx->win);
		julia(keeper->mlx, keeper->jul);
	}
	return (0);
}

int				mouse_press(int button, int x, int y, t_keeper *keeper)
{
	if (keeper->man)
	{
		if (button == SCROLL_UP || button == SCROLL_DOWN)
		{
			keeper->man->addx += (x - SCREEN_W / 2) * 2;
			keeper->man->addy += (y - SCREEN_H / 2) * 2;
		}
		if (button == SCROLL_UP)
			keeper->man->scale *= 1.5;
		if (button == SCROLL_DOWN)
			keeper->man->scale /= 1.5;
		mlx_clear_window(keeper->mlx->mlx, keeper->mlx->win);
		mandelbrot(keeper->mlx, keeper->man);
	}
	if (keeper->jul)
	{
		if (button == SCROLL_UP)
		{
			keeper->jul->addx = (x - SCREEN_W / 2);
			keeper->jul->addy = (y - SCREEN_H / 2);
		}
		if (button == LEFT_CLICK)
		{
			if (keeper->jul->click == 1)
				keeper->jul->click = 0;
			else keeper->jul->click = 1;
		}
		if (button == SCROLL_UP)
			keeper->jul->zoom *= 1.5;
		if (button == SCROLL_DOWN)
			keeper->jul->zoom /= 1.5;
		mlx_clear_window(keeper->mlx->mlx, keeper->mlx->win);
		julia(keeper->mlx, keeper->jul);		
	}
	return (1);
}
