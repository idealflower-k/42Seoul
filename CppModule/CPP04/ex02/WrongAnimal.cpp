/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:55:35 by sanghwal          #+#    #+#             */
/*   Updated: 2023/05/27 22:47:09 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
	: type("\0") {

		std::cout << "[WrongAnimal] Default constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(std::string _type)
	: type(_type) {

		std::cout << "[WrongAnimal] _type constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& origin)
	: type(origin.type) {
		
		std::cout << "[WrongAnimal] Copy constructor called" << std::endl;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& origin) {
	
	std::cout << "[WrongAnimal] assignment constructor called" << std:: endl;
	
	if (this != &origin) {
		this->type = origin.type;
	}
	return (*this);
}

void	WrongAnimal::makeSound(void) const {
	std::cout << "[WrongAnimal] I'm WrongAnimal!!!" << std::endl;
}

std::string	WrongAnimal::getType(void) const {
	std::cout << "[WrongAnimal] getType called" << std::endl;
	return (this->type);
}

WrongAnimal::~WrongAnimal() {
	std::cout << "[WrongAnimal] Destructor called" << std::endl;
}