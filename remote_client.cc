#include <sys/socket.h>
#include <unistd.h>

#include "remote_client.h"

namespace ymarcov {
namespace net {

RemoteClient::RemoteClient(std::pair<int, string> fd_address) :
		_fd{fd_address.first}, address{fd_address.second}
{ }

RemoteClient::~RemoteClient() {
	shutdown(_fd, SHUT_RDWR);
}

size_t RemoteClient::write(const string& data) {
	auto bytesWritten = ::write(_fd, data.data(), data.size());
	if (bytesWritten == -1)
		throw ConnectionError("Failed to write data to client");

	return bytesWritten;
}

string RemoteClient::read(size_t bytes) {
	unique_ptr<char[]> buffer{new char[bytes]};

	auto bytesRead = ::read(_fd, buffer.get(), bytes);
	if (bytesRead == -1)
		throw ConnectionError("Failed to read data from client");

	return string(buffer.get(), bytesRead);
}

} // namespace net
} // namespace ymarcov
