/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:52:58 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/25 16:33:26 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "defines.h"
#include "parser.h"

int	main(int ac, char **av)
{
	t_arg	*args;

	if (ac < 5 && ac < 6)
		ft_print_exit("arguments error\n", 1);
	parser_test(&args, ac, av);
	// parser_args(&args, ac, av);
	system("leaks philosophers");
}
