#ifndef __ADDRINFO__
#define __ADDRINFO__

#include <netdb.h>

#include <boost/lexical_cast.hpp>

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
			throw ConnectionError("Failed to resolve host");
		addrinfo::operator=(*result);
	}

	~Addrinfo() {
		freeaddrinfo(result);
	}

private:
	addrinfo* result;
};

}

#endif
