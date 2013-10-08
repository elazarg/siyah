#ifndef __TCP_LISTENER__
#define __TCP_LISTENER__

#include "remote_client.h"

namespace newnet {

struct Listener {

	virtual void listen() = 0;
	virtual Accepted accept() = 0;

	virtual ~Listener() = 0;
};

struct TcpListener final : Listener {
	TcpListener(int port);
	~TcpListener();

	void listen() override;
	Accepted accept() override;

private:
	const int _fd;
};

} // namespace net

#endif
