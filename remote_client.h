#pragma once

#include <string>

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
