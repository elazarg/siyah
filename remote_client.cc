#include <sys/socket.h>
#include <unistd.h>

#include "remote_client.h"

namespace newnet {

RemoteClient::~RemoteClient() {
	shutdown(fd, SHUT_RDWR);
}

size_t RemoteClient::write(const string& data) {
	auto bytesWritten = ::write(fd, data.data(), data.size());
	if (bytesWritten == -1)
		throw ConnectionError("Failed to write data to client");

	return bytesWritten;
}

string RemoteClient::read(size_t bytes) {
	unique_ptr<char[]> buffer{new char[bytes]};

	auto bytesRead = ::read(fd, buffer.get(), bytes);
	if (bytesRead == -1)
		throw ConnectionError("Failed to read data from client");

	return string(buffer.get(), bytesRead);
}

} // namespace net
