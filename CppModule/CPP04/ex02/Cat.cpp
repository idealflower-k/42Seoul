/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:34:26 by sanghwal          #+#    #+#             */
/*   Updated: 2023/05/26 16:29:34 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.h"

Cat::Cat()
	: AAnimal("Cat") {

	std::cout << "[Cat] Default constructor called" << std::endl;

	this->c_brain = new Brain();
}

Cat::Cat(const Cat& origin)
	: AAnimal(origin), c_brain(origin.c_brain) {

	std::cout << "[Cat] Copy constructor called" << std::endl;
}

Cat& Cat::operator=(const Cat& origin) {
	
	std::cout << "[Cat] Copy assignment called" << std::endl;

	if (this != &origin) {
		AAnimal::operator=(origin);
		this->c_brain = origin.c_brain;
	}
	return (*this);
}

void	Cat::makeSound() const {
	std::cout << "[Cat] Meow~" << std::endl;
}

std::string	Cat::getType(void) const{
	std::cout << "[Cat] getType called" << std::endl;
	return (this->type);
}

Brain*	Cat::getBrain(void) {
	return (this->c_brain);
}

Cat::~Cat() {
	std::cout << "[Cat] Destructor called" << std::endl;

	delete this->c_brain;
}