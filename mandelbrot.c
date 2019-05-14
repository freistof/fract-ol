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

void	*mlx_new_image(void *mlx_ptr,int width,int height);

/*void					mandelbrot(t_mlx mlx, t_man man)
{
	(void)man;
	void				*image;
	char				*address;
	int					*bpp;
	int					*sizeline;
	int					*endian;

	bpp = malloc(sizeof(int));
	sizeline = malloc(sizeof(int));
	endian = malloc(sizeof(int));
	image = mlx_new_image(mlx.mlx, SCREEN_W, SCREEN_H);
	address = mlx_get_data_addr(image, bpp, sizeline, endian);
	for (int i = 0; i < SCREEN_W * SCREEN_H * 4; i += 4)
		address[i] = 120;
	mlx_put_image_to_window(mlx.mlx, mlx.win, image, 0, 0);
}*/

void					mandelbrot(t_mlx mlx, t_man man)
{
	void				*image;
	char				*image_string;
	int					*bpp;
	int					*sizeline;
	int					*endian;
	int					x = 0;

	bpp = malloc(sizeof(int));
	sizeline = malloc(sizeof(int));
	endian = malloc(sizeof(int));
	while (man.x < SCREEN_W / 2)
	{
		image = mlx_new_image(mlx.mlx, 1, SCREEN_H);
		image_string = mlx_get_data_addr(image, bpp, sizeline, endian);
		man.y = SCREEN_H / 2 * -1;
		while (man.y < SCREEN_H / 2)
		{
			man.ax = man.cx + man.x * man.scale;
			man.ay = man.cy + man.y * man.scale;
			man.a1 = man.ax;
			man.b1 = man.ay;
			man.lp = 0;
			while (man.lp <= 250 && man.a1 * man.a1 + man.b1 * man.b1 <= man.limit)
			{
				man.lp += 1;
				man.a2 = man.a1 * man.a1 - man.b1 * man.b1 + man.ax;
				man.b2 = 2 * man.a1 * man.b1 + man.ay;
				man.a1 = man.a2;
				man.b1 = man.b2;
			}
			if (man.lp > 250)
				man.lp = 0;
			//mlx_pixel_put(mlx.mlx, mlx.win, man.x + SCREEN_W / 2, man.y + SCREEN_H / 2, man.lp);
			image_string[x] = man.lp / 2;
			x += 4;
			man.y++;
		}
		mlx_put_image_to_window(mlx.mlx, mlx.win, image, 100, 100);
	//	free(image);
	//	free(image_string);
		man.x++;
	}
	//mlx_put_image_to_window(mlx.mlx, mlx.win, image, 0, 0);
}

void				set_mandelbrot(t_man *man)
{
	man->cx = 0;
	man->cy = 0;
	man->scale = 0.003;
	man->limit = 10000;
	man->lp = 0;
	man->thex = 0;
	man->they = 0;
	man->x = SCREEN_W / 2 * -1;
	man->y = SCREEN_H / 2 * -1;
}
