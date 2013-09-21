#pragma once

#include "remote_client.h"
#include <netdb.h>

namespace ymarcov {
namespace net {

class TcpListener
{
public:
  TcpListener(int port);
  ~TcpListener();

  void Listen();
  RemoteClient AcceptClient();

private:
  static struct addrinfo GetHints();
  void Bind();

  int _port;
  int _fd;
};

} // namespace net
} // namespace ymarcov
