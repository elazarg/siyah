#pragma once

#include <string>

namespace ymarcov {
namespace net {

class RemoteClient
{
public:
  RemoteClient(int fd, std::string address);
  ~RemoteClient();

  const std::string& GetAddress() const;
  size_t Write(const std::string&);
  std::string Read(size_t bytes);

private:
  std::string _address;
  int _fd;
};

} // namespace net
} // namespace ymarcov
