#ifndef __REMOTE_CLIENT
#define __REMOTE_CLIENT

#include "default_include.h"

namespace newnet {

struct Accepted {
	const int fd;
	const string address;
};

struct RemoteClient final : private Accepted {
	using Accepted::Accepted;
	RemoteClient(const Accepted& a) : Accepted(a) { }
	~RemoteClient();

	size_t write(const string&);
	string read(size_t bytes);

	using Accepted::address;
};

} // namespace net

#endif
