##************************************************************************** */
##                                                                           */
##                                                       ::::::::            */
##  create_map.c                                       :+:    :+:            */
##                                                    +:+                    */
##  By: nde-wild <marvin@codam.nl>                   +#+                     */
##                                                  +#+                      */
##  Created: 2019/03/06 11:03:30 by nde-wild      #+#    #+#                 */
##  Updated: 2019/03/06 11:03:33 by nde-wild      ########   odam.nl         */
##                                                                           */
##************************************************************************** */

NAME = fractal

FLAGS = -Wall -Werror -Wextra

LIBM = minilibx_macos/

LIBFT = libft/

LIBMS = minilibx_macos

SRCS = fractol.c

all: $(NAME)

$(NAME):
		@make -C $(LIBM)
		@make -C $(LIBFT)
		@gcc -o $(NAME) $(FLAGS) $(SRCS) -I $(LIBMS) -L $(LIBMS) \
		-lmlx -L $(LIBFT) -lft -framework OpenGL -framework AppKit

clean:
		@make -C $(LIBM) clean
		@make -C $(LIBFT) clean

fclean: clean
		rm -rf fdf
		@make -C $(LIBFT) fclean

re: fclean all
		@make -C $(LIBM) re
		@make -C $(LIBFT) re
