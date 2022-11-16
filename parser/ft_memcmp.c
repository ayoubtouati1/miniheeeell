/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atouati <atouati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:36:18 by atouati           #+#    #+#             */
/*   Updated: 2022/11/04 01:50:24 by atouati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	ft_memcmp(const void *s1, const void *s2)
{
	size_t			i;
	unsigned char	*str_1;
	unsigned char	*str_2;

	str_1 = (unsigned char *)s1;
	str_2 = (unsigned char *)s2;
	i = 0;
	while (str_2[i] || str_1[i])
	{
		if (str_1[i] != str_2[i])
			return (1);
		else
			i++;
	}
	if (str_1[i] != str_2[i])
		return (1);
	return (0);
}
