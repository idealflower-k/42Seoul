#include "DiamondTrap.h"

int	main(void) {

	ScavTrap	scav_1;
	ScavTrap	scav_2("scav_2");
	ScavTrap	scav_3("scav_3");
	FragTrap	frag_1("frag_1");
	FragTrap	frag_2("frag_2");
	DiamondTrap	dia_1("dia_1");
	DiamondTrap	dia_2("dia_2");

	scav_1.attack("target");
	scav_2.attack("scave_3");
	scav_3.takeDamage(20);

	scav_3.beRepaired(10);
	scav_3.attack("scav_2");
	scav_2.takeDamage(120);
	scav_2.beRepaired(10);
	
	scav_2.guardGate();

	ScavTrap scav_4 = scav_3;
	scav_4.takeDamage(10);
	scav_3.takeDamage(0);

	frag_1.attack("some");
	frag_1.takeDamage(0);
	frag_1.highFivesGuys();
	frag_2.highFivesGuys();

	dia_1.attack("dia");
	dia_2.takeDamage(30);
	dia_2.highFivesGuys();
	dia_2.guardGate();
	dia_1.WhoAmI();
	dia_2.WhoAmI();

	DiamondTrap	dia_3(dia_2);
	dia_3.takeDamage(0);
	dia_3 = dia_1;
	dia_3.takeDamage(0);
}
