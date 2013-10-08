#ifndef __TCP_LISTENER__
#define __TCP_LISTENER__

#include "remote_client.h"

namespace ymarcov {
namespace net {

class TcpListener {
public:
	TcpListener(int port);
	~TcpListener();

	void listen();
	pair<int, string> accept();

private:
	int _fd;
};

} // namespace net
} // namespace ymarcov

#endif
