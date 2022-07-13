/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 11:54:42 by sanghwal          #+#    #+#             */
/*   Updated: 2022/07/13 16:15:37 by sanghwal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	s_idx;
	size_t	s_len;
	char	*result;

	if (!s || !f)
		return (0);
	s_len = ft_strlen(s);
	s_idx = 0;
	result = ft_calloc(s_len + 1, sizeof(char));
	if (!result)
		return (0);
	while (s_idx < s_len)
	{
		result[s_idx] = f(s_idx, s[s_idx]);
		s_idx++;
	}
	return (result);
}
