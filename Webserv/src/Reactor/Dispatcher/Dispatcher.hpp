#pragma once
#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

#include "Dispatcher.h"

namespace reactor {

	class Dispatcher : public utils::TSingleton<Dispatcher> {
	   private:
		SyncEventDemultiplexer* _demultiplexer;
		std::map<fd_t, std::vector<u::shared_ptr<AEventHandler> > > _ioHandlers;
		std::map<fd_t, std::vector<u::shared_ptr<AEventHandler> > > _exeHandlers;
		std::map<u::shared_ptr<AEventHandler>, size_t> _handlerIndices;
		std::set<fd_t> _fdsToClose;
		std::vector<u::shared_ptr<AEventHandler> > _removeHandlers;
		std::vector<u::shared_ptr<AEventHandler> > _addHandlers;

		Dispatcher(const Dispatcher& obj);
		Dispatcher& operator=(const Dispatcher& obj);

		void exeHandlerexe();
		void applyHandlersChanges();

	   public:
		Dispatcher();
		~Dispatcher();
		template <class Factory>
		void registerIOHandler(sharedData_t& sharedData) {
			const handle_t handle = sharedData->getFd();
			Factory factory;
			u::shared_ptr<AEventHandler> handler = factory.createIOHandler(sharedData);

			this->_ioHandlers[handle].push_back(handler);
			this->_handlerIndices[handler] = this->_ioHandlers[handle].size() - 1;
			this->_demultiplexer->requestEvent(handler.get(), sharedData->getType());
		}

		template <class Factory>
		void registerExeHandler(sharedData_t sharedData) {
			Factory factory;
			u::shared_ptr<AEventHandler> handler = factory.createExeHandler(sharedData);
			this->_addHandlers.push_back(handler);
		}
		void removeIOHandler(fd_t fd, enum EventType type);
		void removeExeHandler(AEventHandler* handler);
		void addFdToClose(fd_t fd);
		void removeFdToClose(fd_t fd);
		bool isFdMarkedToClose(fd_t fd) const;
		void closePendingFds();
		bool isWriting(fd_t fd) const;

		void handleEvent();
	};
}  // namespace reactor

#endif
