/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:11:52 by amimouni          #+#    #+#             */
/*   Updated: 2021/11/04 15:11:54 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cur;
	unsigned char	*charfind;
	int				len;

	len = ft_strlen(s);
	charfind = NULL;
	cur = (unsigned char *)s;
	while (s != NULL && n--)
	{
		if ((unsigned char)c == 0)
			return (&cur[len]);
		if (*cur != (unsigned char)c)
		{
			cur++;
		}
		else
		{
			charfind = cur;
			return (charfind);
		}
	}
	return (charfind);
}
