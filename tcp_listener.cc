#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <boost/lexical_cast.hpp>

#include "default_include.h"
#include "tcp_listener.h"

namespace {

struct Addrinfo : addrinfo {
	Addrinfo() : result(nullptr) {
		ai_family = AF_INET;
		ai_socktype = SOCK_STREAM;
		ai_flags = AI_PASSIVE;
	}

	explicit Addrinfo(int port) {
		const Addrinfo hints;
		if (getaddrinfo(nullptr, boost::lexical_cast<string>(port).c_str(), &hints, &result))
			throw runtime_error("Failed to resolve host");
		addrinfo::operator=(*result);
	}

	~Addrinfo() {
		freeaddrinfo(result);
	}

private:
	addrinfo* result;
};

}

namespace ymarcov {
namespace net {

TcpListener::TcpListener(int port) {
	const Addrinfo hints;
	_fd = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);
	if (_fd == -1)
		throw runtime_error("Failed to create socket");

	Addrinfo result{port};
	if (::bind(_fd, result.ai_addr, result.ai_addrlen))
		throw runtime_error("Failed to bind socket to the specified port");
}

TcpListener::~TcpListener() {
	shutdown(_fd, SHUT_RDWR);
}

void TcpListener::listen() {
	if (::listen(_fd, SOMAXCONN))
		throw runtime_error("Failed to start listening");
}

pair<int, string> TcpListener::accept() {
	sockaddr_in result;
	socklen_t size = sizeof(result);
	int fd = ::accept(_fd, (sockaddr*) &result, &size);
	if (fd == -1)
		throw runtime_error("Failed to accept client socket");

	return make_pair(fd, inet_ntoa(result.sin_addr));
}

} // namespace net
} // namespace ymarcov
