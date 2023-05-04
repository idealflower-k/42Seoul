/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:36:08 by sanghwal          #+#    #+#             */
/*   Updated: 2023/05/02 14:34:12 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.h"

Weapon::Weapon(std::string _type)
	: type(_type) {}

std::string Weapon::getType() const {
	return (this->type);
}

void	Weapon::setType(std::string _type) {
	this->type = _type;
}