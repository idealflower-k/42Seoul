/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:55:22 by sanghwal          #+#    #+#             */
/*   Updated: 2022/07/07 14:27:21 by sanghwal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c);

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
