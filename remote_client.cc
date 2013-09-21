#include "remote_client.h"

#include <memory>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

namespace ymarcov {
namespace net {

RemoteClient::RemoteClient(int fd, std::string address)
  : _fd(fd)
  , _address(std::move(address))
{}

RemoteClient::~RemoteClient()
{
  shutdown(_fd, SHUT_RDWR);
}

const std::string& RemoteClient::GetAddress() const
{
	return _address;
}

size_t RemoteClient::Write(const std::string& data)
{
  auto bytesWritten = write(_fd, data.data(), data.size());

  if (bytesWritten == -1)
    throw std::runtime_error("Failed to write data to client");

  return bytesWritten;
}

std::string RemoteClient::Read(size_t bytes)
{
  std::unique_ptr<char[]> buffer(new char[bytes]);

  auto bytesRead = read(_fd, buffer.get(), bytes);

  if (bytesRead == -1)
    throw std::runtime_error("Failed to read data from client");

  return std::string(buffer.get(), bytesRead);
}

} // namespace net
} // namespace ymarcov
