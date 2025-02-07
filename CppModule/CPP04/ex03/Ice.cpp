#include "Ice.hpp"

Ice::Ice()
	: AMateria("ice") {

	std::cout << "[Ice] Default constructor called" << std::endl;
}

Ice::Ice(const Ice& origin)
	: AMateria(origin) {

	this->_type = "ice";
	std::cout << "[Ice] Copy constructor called" << std::endl;
}

Ice& Ice::operator=(const Ice& origin) {
	
	std::cout << "[Ice] Copy assignment called" << std::endl;
	
	if (this != &origin) {
		AMateria::operator=(origin);
		this->_type = "ice";
	}
	return (*this);
}

AMateria* Ice::clone(void) const {

	AMateria* temp = new Ice(*this);
	return (temp);
}

void	Ice::use(ICharacter& target) {
	std::cout << "Ice: \"* shoots an ice bolt at " << target.getName() << " *\"" << std::endl;
}

Ice::~Ice() {
	std::cout << "[Ice] Destructor called" << std::endl;
}
