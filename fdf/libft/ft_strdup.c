/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:46:33 by sanghwal          #+#    #+#             */
/*   Updated: 2022/07/19 21:08:33 by sanghwal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char			*temp;
	const size_t	size = ft_strlen(src);
	size_t			i;

	temp = ft_calloc(size + 1, sizeof(char));
	if (!temp)
		return (0);
	i = 0;
	while (src[i])
	{
		temp[i] = src[i];
		i++;
	}
	return (temp);
}
