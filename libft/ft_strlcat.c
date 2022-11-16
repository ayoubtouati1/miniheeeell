/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:53:23 by amimouni          #+#    #+#             */
/*   Updated: 2021/11/04 14:54:49 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	srlen;
	size_t	res;
	size_t	i;
	char	*s;

	dlen = ft_strlen(dst);
	srlen = ft_strlen(src);
	res = dlen + srlen;
	if (dst == NULL && dstsize == 0)
		return (srlen);
	s = (char *)src;
	if (dstsize <= dlen)
		return (srlen + dstsize);
	i = 0;
	while (s[i] && dstsize - 1 > dlen)
	{
		dst[dlen] = s[i];
		i++;
		dlen++;
	}
	dst[dlen] = '\0';
	return (res);
}
