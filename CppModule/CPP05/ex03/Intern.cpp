/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:29:52 by sanghwal          #+#    #+#             */
/*   Updated: 2023/07/19 15:10:17 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern() {}

Intern::Intern(const Intern& origin) {
	(void)origin;
}

Intern&	Intern::operator=(const Intern& origin) {
	if (this != &origin)
		Intern::operator=(origin);
	return (*this);
}

AForm*	Intern::makeForm(std::string form, std::string target) {
	AForm	*res = NULL;
	std::string forms[3] = \
	{"ShrubberyCreationForm", "RobotomyRequestForm", "PresidentialPardonForm"};
	int			idx = -1;

	while (idx < 3 && form.compare(forms[++idx])) {}

	switch (idx)
	{
	case 0:
		res = new ShrubberyCreationForm(target);
		break;
	case 1:
		res = new RobotomyRequestForm(target);
		break;
	case 2:
		res = new PresidentialPardonForm(target);
		break;
	default:
		std::cerr << "Have Not Form\n";
		return (NULL);
	}
	std::cout << "Intern creates " << form << "\n";
	return (res);
}

Intern::~Intern() {
	std::cout << "[Intern] Destructor called\n";
}