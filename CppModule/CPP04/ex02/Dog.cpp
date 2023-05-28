/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:44:10 by sanghwal          #+#    #+#             */
/*   Updated: 2023/05/28 17:55:27 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
	: AAnimal("Dog") {
	
	std::cout << "[Dog] Default constructor called" << std::endl;

	this->d_brain = new Brain();
}

Dog::Dog(const Dog& origin)
	: AAnimal(origin) {
	
	std::cout << "[Dog] Copy constructor called" << std::endl;
	
	this->d_brain = new Brain(*origin.d_brain);
}

Dog& Dog::operator=(const Dog& origin) {

	std::cout << "[Dog] Copy assignment called" << std::endl;
	
	if (this != &origin) {
		AAnimal::operator=(origin);
		*this->d_brain = *origin.d_brain;
	}
	return (*this);
}

void	Dog::makeSound(void) const{
	std::cout << "[Dog] woof!" << std::endl;
}

std::string	Dog::getType(void) const{
	std::cout << "[Dog] getType called" << std::endl;
	return (this->type);
}

Brain*	Dog::getBrain(void) {
	return (this->d_brain);
}

std::string	Dog::getIdeasIdx(int idx) const {
	return (this->d_brain->getIdeasIdx(idx));
}

void	Dog::addIdeas(const std::string& some) {
	this->d_brain->addIdeas(some);
}

Dog::~Dog() {
	std::cout << "[Dog] Destructor called" << std::endl;

	delete this->d_brain;
}
