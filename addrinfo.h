#ifndef __ADDRINFO__
#define __ADDRINFO__

#include <netdb.h>

namespace {

struct Addrinfo : addrinfo {
	Addrinfo() : result(nullptr) {
		ai_family = AF_INET;
		ai_socktype = SOCK_STREAM;
		ai_flags = AI_PASSIVE;
		ai_protocol = IPPROTO_TCP;
	}

	explicit Addrinfo(int port);

	~Addrinfo() {
		freeaddrinfo(result);
	}

private:
	addrinfo* result;
};

const Addrinfo hints;

Addrinfo::Addrinfo(int port) {
	if (getaddrinfo(nullptr, itoa(port), &hints, &result))
		throw ConnectionError("Failed to resolve host");
	addrinfo::operator=(*result);
}

}

#endif
