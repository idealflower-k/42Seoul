#ifndef VERSION_H
#define VERSION_H

#include "color.h"

#ifndef CHK_VER
#define CHK_VER(ver) (ver == 199711 ? "C++98" : "Not C++98")
#endif

#ifndef PRT_VER
#define PRT_VER std::cout << "cpp version: " YELLOW << CHK_VER(__cplusplus) << RESET "\n\n"
#endif

#ifndef V
#define V 0
#endif

#ifndef VERBOSE
#define VERBOSE(STR) \
	if (V)           \
		std::cout << STR << std::endl;
#endif
#endif
