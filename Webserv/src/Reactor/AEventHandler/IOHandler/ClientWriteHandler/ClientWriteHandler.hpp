#pragma once
#ifndef CLIENTWRITEHANDLER_HPP
#define CLIENTWRITEHANDLER_HPP

#include "ClientWriteHandler.h"

namespace reactor {
	class ClientWriteHandler : public AEventHandler {
	   private:
		ClientWriteHandler(const ClientWriteHandler& obj);

	   public:
		ClientWriteHandler(sharedData_t& sharedData);
		~ClientWriteHandler();
		virtual void handleEvent();
	};

}  // namespace reactor

#endif
