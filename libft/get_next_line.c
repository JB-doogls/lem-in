/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:11:38 by edoll             #+#    #+#             */
/*   Updated: 2020/08/25 23:03:16 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		write_last(t_gnl **list, t_gnl **l_head, char **line)
{
	char *is_feed;

	if (!(*list)->content)
	{
		*line = NULL;
		return (0);
	}
	*line = ft_strdup((*list)->content);
	if (!(ft_strlen(*line)))
		return (0);
	is_feed = ft_strchr((*list)->content, '\n');
	free((*list)->content);
	(*list)->content = NULL;
	*list = *l_head;
	if (!is_feed)
		return (1);
	else
		return (0);
}

int		rec_line(char **cont, char *buff)
{
	if (*cont)
	{
		if (!(*cont = ft_strjoin_free(*cont, buff)))
			return (-1);
	}
	else if (!(*cont = ft_strdup(buff)))
		return (-1);
	return (0);
}

int		check_line(char **cont, char **line, t_gnl **list, t_gnl **l_head)
{
	char	*pos;
	char	*tmp;

	if (!(*cont) || !(ft_strchr(*cont, '\n')))
		return (0);
	pos = ft_strchr(*cont, '\n');
	tmp = *cont;
	*pos++ = '\0';
	if (!((*line) = ft_strdup(*cont)))
		return (-1);
	if (!(*line) || !(*cont = ft_strdup(pos)))
		return (-1);
	free(tmp);
	*list = *l_head;
	return (1);
}

int		set_list(t_gnl **list, t_gnl **l_head, int fd)
{
	if (!(*list))
		if (!((*list) = ft_lstnewset(fd)))
			return (-1);
	*l_head = *list;
	while ((*list)->fd != fd && (*list)->next)
		*list = (*list)->next;
	if ((*list)->fd != fd)
	{
		if (!((*list)->next = ft_lstnewset(fd)))
			return (-1);
		*list = (*list)->next;
	}
	return (1);
}

int		get_next_line(int const fd, char **line, int clean)
{
	static t_gnl	*list;
	t_gnl			*l_head;
	size_t			ret;
	char			buff[BUFF_SIZE + 1];

	if (clean)
		return (clean_gnl_cache(list));
	if (fd < 0 || BUFF_SIZE <= 0 || !line || read(fd, NULL, 0) < 0)
		return (-1);
	if (set_list(&list, &l_head, fd) == -1)
		return (-1);
	ret = check_line(&(list->content), line, &list, &l_head);
	if (ret)
		return (ret);
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		buff[ret] = '\0';
		if (rec_line(&(list->content), buff))
			return (-1);
		ret = check_line(&(list->content), line, &list, &l_head);
		if (ret)
			return (ret);
	}
	return (write_last(&list, &l_head, line));
}
