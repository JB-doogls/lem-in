/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:04:40 by edoll             #+#    #+#             */
/*   Updated: 2020/09/10 01:18:28 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t ct;

	ct = 0;
	if (!s1[ct] && !s2[ct])
		return (0);
	while (s1[ct] && s2[ct] && s1[ct] == s2[ct])
		ct++;
	return ((unsigned char)s1[ct] - (unsigned char)s2[ct]);
}
