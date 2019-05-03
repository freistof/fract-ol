#******************************************************************************#
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fblom <marvin@codam.nl>                      +#+                      #
#                                                    +#+                       #
#    Created: 2019/05/02 15:07:19 by fblom         #+#    #+#                  #
#    Updated: 2019/05/02 15:07:19 by fblom         ########   odam.nl          #
#                                                                              #
#******************************************************************************#

NAME = fractol

FLAGS = -Wall -Werror -Wextra

LIBM = minilibx_macos/

LIBFT = libft/

LIBMS = minilibx_macos

SRCS = fractol.c keys.c mandelbrot.c julia.c

all: $(NAME)

$(NAME):
		make -C $(LIBM)
		make -C $(LIBFT)
		gcc -o $(NAME) $(FLAGS) $(SRCS) -I $(LIBMS) -L $(LIBMS) \
		-lmlx -L $(LIBFT) -lft -framework OpenGL -framework AppKit

again:
	gcc -o $(NAME) $(FLAGS) $(SRCS) -I $(LIBMS) -L $(LIBMS) \
		-lmlx -L $(LIBFT) -lft -framework OpenGL -framework AppKit

clean:
		make -C $(LIBM) clean
		make -C $(LIBFT) clean

fclean: clean
		rm -rf $(NAME)
		make -C $(LIBFT) fclean

re: fclean all
		make -C $(LIBM) re
		make -C $(LIBFT) re
