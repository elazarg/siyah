#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "default_include.h"
#include "tcp_listener.h"
#include "addrinfo.h"

namespace ymarcov {
namespace net {

TcpListener::TcpListener(int port) {
	const Addrinfo hints;
	_fd = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);
	if (_fd == -1)
		throw ConnectionError("Failed to create socket");

	Addrinfo result{port};
	if (::bind(_fd, result.ai_addr, result.ai_addrlen))
		throw ConnectionError("Failed to bind socket to the specified port");
}

TcpListener::~TcpListener() {
	shutdown(_fd, SHUT_RDWR);
}

void TcpListener::listen() {
	if (::listen(_fd, SOMAXCONN))
		throw ConnectionError("Failed to start listening");
}

pair<int, string> TcpListener::accept() {
	sockaddr_in result;
	socklen_t size = sizeof(result);
	int fd = ::accept(_fd, (sockaddr*) &result, &size);
	if (fd == -1)
		throw ConnectionError("Failed to accept client socket");

	return make_pair(fd, inet_ntoa(result.sin_addr));
}

} // namespace net
} // namespace ymarcov
