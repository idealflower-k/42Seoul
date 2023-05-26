/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:44:10 by sanghwal          #+#    #+#             */
/*   Updated: 2023/05/26 16:25:30 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.h"

Dog::Dog()
	: Animal("Dog") {
	
	std::cout << "[Dog] Default constructor called" << std::endl;
}

Dog::Dog(const Dog& origin)
	: Animal(origin.type) {
	
	std::cout << "[Dog] Copy constructor called" << std::endl;
}

Dog& Dog::operator=(const Dog& origin) {

	std::cout << "[Dog] Copy assignment called" << std::endl;
	
	if (this != &origin)
		Animal::operator=(origin);
	return (*this);
}

void	Dog::makeSound(void) const{
	std::cout << "[Dog] woof!" << std::endl;
}

std::string	Dog::getType(void) const{
	std::cout << "[Dog] getType called" << std::endl;
	return (this->type);
}

Dog::~Dog() {
	std::cout << "[Dog] Destructor called" << std::endl;
}