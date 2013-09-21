#include "remote_client.h"

#include <memory>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

namespace ymarcov {
namespace net {

RemoteClient::RemoteClient(int fd)
  : _fd(fd)
{
}

RemoteClient::~RemoteClient()
{
  shutdown(_fd, SHUT_RDWR);
}

size_t RemoteClient::WriteLine(const std::string& data)
{
  auto bytesWritten = write(_fd, data.data(), data.size());

  if (bytesWritten == -1)
    throw std::runtime_error("Failed to write data to client");

  if (write(_fd, "\n", 1) == -1)
    throw std::runtime_error("Failed to write line terminator to client");

  return ++bytesWritten;
}

// TODO Actually read until a line-terminator is found
std::string RemoteClient::ReadLine()
{
  static const size_t bufferSize = 0x1000;
  std::unique_ptr<char[]> buffer(new char[bufferSize]);

  auto bytesRead = read(_fd, buffer.get(), bufferSize);

  if (bytesRead == -1)
    throw std::runtime_error("Failed to read data from client");

  return std::string(buffer.release(), bytesRead);
}

} // namespace net
} // namespace ymarcov
