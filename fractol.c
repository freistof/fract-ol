/** ************************************************************************** */
/**                                                                            */
/**                                                        ::::::::            */
/**   create_map.c                                       :+:    :+:            */
/**                                                     +:+                    */
/**   By: nde-wild <marvin@codam.nl>                   +#+                     */
/**                                                   +#+                      */
/**   Created: 2019/03/06 11:03:30 by nde-wild      #+#    #+#                 */
/**   Updated: 2019/03/06 11:03:33 by nde-wild      ########   odam.nl         */
/**                                                                            */
/** ************************************************************************** */

#include "fractol.h"
/*
void			open_window()
{
	void		*mlx;
	void		*win;


}
*/
int				main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Usage: ./fractol [fractol]\n");
		printf("-m for Mandelbrot\n");
		printf("-j for Julia\n");
		printf("-s for Sierpienski Gasket\n");
		return (0);
	}
	printf("%s\n", argv[1]);
//	open_window();
	return (0);
}
