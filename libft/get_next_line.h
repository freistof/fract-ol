/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbom <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/13 17:32:19 by fblom         #+#    #+#                 */
/*   Updated: 2019/02/13 17:32:23 by fblom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 10
# include <stdlib.h>
# include "libft.h"

int get_next_line(const int fd, char **line);

#endif
