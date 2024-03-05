#pragma once
#ifndef AEXEHANDLER_HPP
#define AEXEHANDLER_HPP

#include "AExeHandler.h"

namespace reactor {
	class AExeHandler : public AEventHandler {
	   protected:
		bool removeHandlerIfNecessary();
		AExeHandler(const AExeHandler& obj);
		AExeHandler& operator=(const AExeHandler& obj);

	   public:
		AExeHandler(sharedData_t sharedData) : AEventHandler(sharedData){};
		virtual ~AExeHandler(){};
	};

}  // namespace reactor

#endif
