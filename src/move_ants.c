/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 01:52:24 by user              #+#    #+#             */
/*   Updated: 2020/09/15 02:03:54 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

void		set_ants_on_paths(t_frame *stor)
{
	t_path		*path_copy;
	int			ants_ct;

	ants_ct = stor->start->ants;
	path_copy = stor->paths;
	while (ants_ct != 0)
	{
		while (path_copy->next && path_copy->len + path_copy->ants_togo <=
		path_copy->next->len + path_copy->next->ants_togo)
		{
			path_copy->ants_togo++;
			ants_ct--;
		}
		if (!path_copy->next)
		{
			path_copy->ants_togo++;
			ants_ct--;
		}
		path_copy = path_copy->next ? path_copy->next : stor->paths;
	}
}

void		move_through_path(t_path *path, t_frame *stor)
{
	t_link		*link;

	link = path->end;
	if (!path->on_work || link->room->level == INT_MAX)
	{
		link->room->level == INT_MAX ? move_simple_path(path, stor) :
		move_from_start(path, stor);
		return ;
	}
	while (link)
	{
		if (link->room->level == 0 && stor->start->ants)
			move_from_start(path, stor);
		else if (link->room->ants)
		{
			if (link->next->room->level == INT_MAX)
				move_to_end(link, path, stor);
			else if (!link->next->room->ants)
				move_by_mid(link);
		}
		link = link->prev;
	}
}

void		handle_ants_move(t_frame *stor)
{
	t_path		*path_copy;

	if (!stor)
		lem_error(ANTS_MOVE_ERR, stor);
	path_copy = stor->paths;
	set_ants_on_paths(stor);
	while (stor->end->ants < stor->num_ants)
	{
		if (path_copy->ants_pass != path_copy->ants_togo)
			move_through_path(path_copy, stor);
		if (path_copy->next)
			path_copy = path_copy->next;
		else
		{
			move_through_path(path_copy, stor);
			path_copy = stor->paths;
			printf("\n");				// refactore to ft_printf
		}
	}
	if (stor->end->ants != stor->num_ants)
		lem_error(MOVE_RES_ERR, stor);
}
