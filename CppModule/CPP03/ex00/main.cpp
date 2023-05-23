/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:56:53 by sanghwal          #+#    #+#             */
/*   Updated: 2023/05/23 20:10:37 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.h"

int	main(void) {

	ClapTrap	clap_1;
	ClapTrap	clap_2("clap_2");
	ClapTrap	clap_3("clap_3");

	clap_1.attack("clap_2");
	clap_2.takeDamage(2);
	clap_2.attack("clap_3");
	clap_3.takeDamage(11);
	
	clap_2.beRepaired(4);

	clap_3.beRepaired(6);
	clap_3.attack("clap_2");
	
	clap_2.takeDamage(0);
	clap_3.takeDamage(3);
}