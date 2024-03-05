#ifndef WEAPON_HPP
# define WEAPON_HPP

class Weapon {
	private :
		std::string type;
	public :
		Weapon(std::string _type);
		std::string	getType() const;
		void		setType(std::string _type);
};

#endif
