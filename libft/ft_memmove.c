/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 09:54:04 by amimouni          #+#    #+#             */
/*   Updated: 2021/11/04 09:54:13 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	*ft_memov2(void *s1, const void *s2, size_t n)
{
	char	*c1;
	char	*c2;

	if (n == 0 || s1 == s2)
	{
		return (s1);
	}
	c1 = (char *)s1;
	c2 = (char *)s2;
	while (n--)
	{
		c1[n] = c2[n];
	}
	return (s1);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst < src)
	{
		return (ft_memcpy(dst, src, len));
	}
	if (dst > src)
	{
		return (ft_memov2(dst, src, len));
	}
	return (dst);
}
