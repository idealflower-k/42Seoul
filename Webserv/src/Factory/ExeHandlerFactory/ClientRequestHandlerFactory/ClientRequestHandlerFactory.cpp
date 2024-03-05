#include "ClientRequestHandlerFactory.hpp"

namespace reactor {
	ClientRequestHandlerFactory::ClientRequestHandlerFactory() {}
	ClientRequestHandlerFactory::~ClientRequestHandlerFactory() {}

	utils::shared_ptr<AEventHandler> ClientRequestHandlerFactory::createExeHandler(sharedData_t& sharedData) {
		return utils::static_pointer_cast<AEventHandler, ClientRequestHandler>(
			utils::shared_ptr<ClientRequestHandler>(new ClientRequestHandler(sharedData)));
	}
}  // namespace reactor
