#include "tcp_listener.h"

#include <arpa/inet.h>
#include <boost/lexical_cast.hpp>
#include <stdexcept>
#include <memory>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

namespace ymarcov {
namespace net {

TcpListener::TcpListener(int port)
  : _port(port)
{
  auto hints = GetHints();

  _fd = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);

  if (_fd == -1)
    throw std::runtime_error("Failed to create socket");

  Bind();
}

TcpListener::~TcpListener()
{
  shutdown(_fd, SHUT_RDWR);
}

void TcpListener::Listen()
{
  if (listen(_fd, SOMAXCONN))
    throw std::runtime_error("Failed to start listening");
}

RemoteClient TcpListener::AcceptClient()
{
  sockaddr_in result;
  socklen_t size = sizeof(result);
  int fd = accept(_fd, (sockaddr*)&result, &size);

  if (fd == -1)
    throw std::runtime_error("Failed to accept client socket");

  return RemoteClient(fd, inet_ntoa(result.sin_addr));
}

struct addrinfo TcpListener::GetHints()
{
  struct addrinfo hints = {0};

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  return hints;
}

void TcpListener::Bind()
{
  struct addrinfo* result;

  {
    auto hints = GetHints();

    if (getaddrinfo(nullptr, boost::lexical_cast<std::string>(_port).c_str(), &hints, &result))
      throw std::runtime_error("Failed to resolve host");
  }

  struct ScopedAddrInfo
  {
    ScopedAddrInfo(struct addrinfo* ai) : _ai(ai) {}
    ~ScopedAddrInfo() { freeaddrinfo(_ai); }
    struct addrinfo* _ai;
  } scopedAddrInfo(result);

  if (bind(_fd, result->ai_addr, result->ai_addrlen))
    throw std::runtime_error("Failed to bind socket to the specified port");
}

} // namespace net
} // namespace ymarcov
