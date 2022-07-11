/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:05:36 by sanghwal          #+#    #+#             */
/*   Updated: 2022/07/11 16:39:50 by sanghwal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			sub_idx;
	unsigned int	s_len;

	if (s == 0)
		return (0);
	s_len = (unsigned int)ft_strlen(s);
	sub_idx = 0;
	if (start >= s_len)
	{
		substr = ft_calloc(1, sizeof(*s));
		if (!substr)
			return (0);
		return (substr);
	}
	if (s_len < len)
		substr = ft_calloc(((s_len - start) + 1), sizeof(*s));
	else
		substr = ft_calloc((len + 1), sizeof(*s));
	if (!substr)
		return (0);
	while (s[start] && sub_idx < len)
		substr[sub_idx++] = s[start++];
	return (substr);
}