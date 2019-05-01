/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fblom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/30 16:47:16 by fblom         #+#    #+#                 */
/*   Updated: 2019/01/30 16:47:16 by fblom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_createsave(char *buf, char *str, char **line, int ret)
{
	char	*save;

	*line = ft_strsub(str, 0, ft_substring_size(str, '\n'));
	if (str[0] == '\0' && ret == 0)
		save = NULL;
	else
		save = ft_strdup(buf + ft_substring_size(buf, '\n') + 1);
	ft_strdel(&buf);
	if (str)
		ft_strdel(&str);
	return (save);
}

static char		*ft_makestr(const int fd, char *save, char **line)
{
	char	buf[BUFF_SIZE + 1];
	char	*str;
	char	*temp;
	int		ret;

	str = ft_strdup(save);
	ret = ft_strlen(str);
	if (str[ft_substring_size(str, '\n')] == '\n')
		return (ft_createsave(save, str, line, ret));
	ft_strdel(&save);
	ret = read(fd, buf, BUFF_SIZE);
	while (ret > 0)
	{
		temp = ft_strdup(str);
		ft_strdel(&str);
		buf[ret] = '\0';
		str = ft_strjoin(temp, buf);
		ft_strdel(&temp);
		temp = NULL;
		if (str[ft_substring_size(str, '\n')] == '\n')
			return (ft_createsave(ft_strdup(buf), str, line, ret));
		ft_strclr(buf);
		ret = read(fd, buf, BUFF_SIZE);
	}
	return (ft_createsave(ft_strnew(1), str, line, ret));
}

static void		addtolst(t_list **list, t_list **head)
{
	*list = *head;
	ft_lstadd(list, ft_lstnew("\0", 1));
	*head = *list;
}

static char		*fd_checker(const int fd, char *save)
{
	static t_list	*list;
	t_list			*head;

	if (!list)
	{
		list = ft_lstnew("\0", 1);
		list->content_size = fd;
	}
	head = list;
	while (fd != (int)list->content_size && list->next != NULL)
		list = list->next;
	if (fd != (int)list->content_size && list->next == NULL)
	{
		addtolst(&list, &head);
		list->content_size = fd;
	}
	if (save == NULL)
		save = ft_strdup(list->content);
	else
	{
		ft_memdel(&list->content);
		list->content = save;
	}
	list = head;
	return (save);
}

int				get_next_line(const int fd, char **line)
{
	static char			*save;

	save = NULL;
	if (fd == -1 || read(fd, save, 0) == -1)
		return (-1);
	save = fd_checker(fd, save);
	save = ft_makestr(fd, save, line);
	if (save == NULL)
	{
		if (read(fd, save, BUFF_SIZE) == 0)
		{
			ft_strdel(&save);
			return (0);
		}
	}
	save = fd_checker(fd, save);
	return (1);
}
