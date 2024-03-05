#include "FileReadHandler.hpp"

namespace reactor {
	FileReadHandler::FileReadHandler(sharedData_t& sharedData) : AEventHandler(sharedData) {
		if (fcntl(this->getHandle(), F_SETFL, O_NONBLOCK, FD_CLOEXEC) < 0) {
			ErrorLogger::systemCallError(__FILE__, __LINE__, __func__);
			this->setState(TERMINATE);
		}
	}

	FileReadHandler::~FileReadHandler() {}

	void FileReadHandler::handleEvent() {
		if (this->getState() == TERMINATE || this->getState() == RESOLVE)
			return;
		std::vector<char> buffer(BUFFER_SIZE);
		ssize_t readByte = read(this->getHandle(), buffer.data(), BUFFER_SIZE - 1);

		if (readByte == -1) {
			ErrorLogger::systemCallError(__FILE__, __LINE__, __func__, "read fail");
			this->setState(TERMINATE);
			return;
		}
		if (readByte < BUFFER_SIZE - 1) {
			this->getBuffer().insert(this->getBuffer().end(), buffer.begin(), buffer.begin() + readByte);
			this->setState(RESOLVE);
			return;
		}
		this->getBuffer().insert(this->getBuffer().end(), buffer.begin(), buffer.begin() + readByte);
	}
}  // namespace reactor
