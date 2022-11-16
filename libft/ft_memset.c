/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amimouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:21:50 by amimouni          #+#    #+#             */
/*   Updated: 2021/11/03 20:35:14 by amimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char		*cur;
	size_t				i;

	if (len == 0)
	{
		return (b);
	}
	cur = (unsigned char *)b;
	i = 0;
	while (len)
	{
		cur[i] = (unsigned char)c;
		i++;
		len--;
	}
	return (b);
}
