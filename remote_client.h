#ifndef __REMOTE_CLIENT
#define __REMOTE_CLIENT

#include "default_include.h"

namespace ymarcov {
namespace net {

class RemoteClient
{
public:
  RemoteClient(pair<int, string> fd_address);
  ~RemoteClient();

  const string& getAddress() const;
  size_t write(const string&);
  string read(size_t bytes);

private:  int _fd;
private:  string _address;
};

} // namespace net
} // namespace ymarcov

#endif
