#include "SyncEventDemultiplexer.hpp"

namespace reactor {
	SyncEventDemultiplexer::SyncEventDemultiplexer() : _kq(Kqueue::getInstance()) {
		this->_timeout.tv_sec = 0;
		this->_timeout.tv_nsec = 0;
	}
	SyncEventDemultiplexer::~SyncEventDemultiplexer() {}

	void SyncEventDemultiplexer::requestEvent(AEventHandler* handler, const enum EventType type) {
		if (type == EVENT_TIMER) {
			this->_kq->AddEventOnChangeList(handler->getHandle(), type, EV_ADD, 0, handler->getReadByte(), handler);
			return;
		}
		this->_kq->AddEventOnChangeList(handler->getHandle(), type, EV_ADD, 0, 0, handler);
	}

	void SyncEventDemultiplexer::unRequestEvent(AEventHandler* handler, const enum EventType type) {
		this->_kq->AddEventOnChangeList(handler->getHandle(), type, EV_DELETE, 0, 0, u::nullptr_t);
	}

	void SyncEventDemultiplexer::unRequestAllEvent(fd_t fd) {
		this->_kq->AddEventOnChangeList(fd, EVFILT_READ, EV_DELETE, 0, 0, u::nullptr_t);
		this->_kq->AddEventOnChangeList(fd, EVFILT_WRITE, EV_DELETE, 0, 0, u::nullptr_t);
	}

	void SyncEventDemultiplexer::setFdTime(fd_t fd, std::time_t curTime) {
		this->_fdsTime[fd] = curTime;
	}

	void SyncEventDemultiplexer::eraseFdTime(fd_t fd) {
		this->_fdsTime.erase(fd);
	}

	std::time_t SyncEventDemultiplexer::getFdTime(fd_t fd) {
		if (this->_fdsTime.find(fd) != this->_fdsTime.end())
			return this->_fdsTime[fd];
		return (0);
	}

	void SyncEventDemultiplexer::waitEvents(void) {
		this->_kq->checkSize();
		const int eventNum =
			kevent(this->_kq->getFd(), &this->_kq->getChangeList()[0], this->_kq->getChangeList().size(),
				   &this->_kq->getkEventList()[0], this->_kq->getkEventList().size(), &this->_timeout);
		if (eventNum == SYSTEMCALL_ERROR)
			ErrorLogger::systemCallError(__FILE__, __LINE__, __func__);
		this->_kq->getChangeList().clear();
		for (int i = 0; i < eventNum; ++i) {
			if (this->_kq->getkEventList()[i].flags & EV_ERROR) {
				continue;
			}
			this->setFdTime(this->_kq->getkEventList()[i].ident, std::time(NULL));
			static_cast<AEventHandler*>(this->_kq->getkEventList()[i].udata)->handleEvent();
		}
	};
}  // namespace reactor
