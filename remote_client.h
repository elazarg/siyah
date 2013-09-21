#pragma once

#include <string>

namespace ymarcov {
namespace net {

class RemoteClient
{
public:
  RemoteClient(int fd);
  ~RemoteClient();

  size_t Write(const std::string&);
  std::string Read(size_t bytes);

private:
  int _fd;
};

} // namespace net
} // namespace ymarcov
