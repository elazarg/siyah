#pragma once

#include <string>

namespace ymarcov {
namespace net {

class RemoteClient
{
public:
  RemoteClient(int fd);
  ~RemoteClient();

  size_t WriteLine(const std::string&);
  std::string ReadLine();

private:
  int _fd;
};

} // namespace net
} // namespace ymarcov
