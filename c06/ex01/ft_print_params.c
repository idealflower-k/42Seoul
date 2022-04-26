/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:01:36 by sanghwal          #+#    #+#             */
/*   Updated: 2022/04/26 20:21:58 by sanghwal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int ac, char **ag)
{
	int	i;
	int	j;
	int	temp;

	temp = ac;
	i = 1;
	j = 0;
	while (ag[i])
	{
		j = 0;
		while (ag[i][j])
		{
			write(1, &ag[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
