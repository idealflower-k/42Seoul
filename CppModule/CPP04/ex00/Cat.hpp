#ifndef CAT_HPP
# define CAT_HPP

#include "Animal.hpp"

class Cat : public Animal {

	public:
		Cat();
		Cat(const Cat& origin);

		Cat&		operator=(const Cat& origin);

		void		makeSound(void) const;
		std::string	getType(void) const;

		~Cat();
};

#endif
