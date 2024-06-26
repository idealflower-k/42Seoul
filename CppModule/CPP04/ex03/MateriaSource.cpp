#include "MateriaSource.hpp"

const int	MateriaSource::learn_size = 4;

MateriaSource::MateriaSource()
	: IMateriaSource() {

	std::cout << "[MateriaSource] Default constructor called" << std::endl;

	this->learned = new AMateria*[learn_size];

	for (int i = 0; i < learn_size; ++i)
		this->learned[i] = NULL;
}

MateriaSource::MateriaSource(const MateriaSource& origin)
	: IMateriaSource() {

	std::cout << "[MateriaSource] Copy constructor called" << std::endl;

	this->learned = new AMateria*[learn_size];

	for (int i = 0; i < learn_size; ++i)
		this->learned[i] = origin.learned[i] ? origin.learned[i]->clone() : NULL;
}

MateriaSource& MateriaSource::operator=(const MateriaSource& origin) {

	std::cout << "[MateriaSource] Copy assignment called" << std::endl;

	if (this != &origin) {
		IMateriaSource::operator=(origin);

		for (int i = 0; i < learn_size; ++i) {
			if (this->learned[i] != NULL)
				delete this->learned[i];
			this->learned[i] = origin.learned[i] ? origin.learned[i]->clone() : NULL;
		}
	}
	return (*this);
}

void	MateriaSource::learnMateria(AMateria* m) {
	
	for (int i = 0; i < learn_size; ++i) {
		if (this->learned[i] == NULL) {
			this->learned[i] = m->clone();
			return ;
		}
	}
}

AMateria*	MateriaSource::createMateria(std::string const& type) {

	for (int i = 0; i < learn_size; ++i) {
		if (this->learned[i] != NULL && !this->learned[i]->getType().compare(type)) {
			return (this->learned[i]->clone());
		}
	}
	return (0);
}

MateriaSource::~MateriaSource() {
	std::cout << "[MateriaSource] Destructor called" << std::endl;
	
	for (int i = 0; i < learn_size; ++i) {
		if (this->learned[i] != NULL)
			delete this->learned[i];
	}
	delete[] this->learned;
}
