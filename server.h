#pragma once

#include "remote_client.h"

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
