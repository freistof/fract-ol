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

FLAGS = -Wall -Werror -Wextra -lpthread -g

# FLAGS = -Wall -Werror -Wextra

LIBM = minilibx_macos/

LIBFT = libft/

LIBMS = minilibx_macos

SRCS = fractol.c loops.c draw.c keys.c threads.c

OFILES := fractol.o loops.o draw.o keys.o threads.o

all: $(NAME)

$(NAME):
		make -C $(LIBM)
		make -C $(LIBFT)
		gcc -c $(SRCS)
		gcc -o $(NAME) $(FLAGS) $(OFILES) -I $(LIBMS) -L $(LIBMS) \
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
