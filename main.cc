#include "tcp_listener.h"

#include <iostream>

int main(int argc, char** argv)
{
  ymarcov::net::TcpListener listener(1334);
  listener.Listen();

  auto client = listener.AcceptClient();
  std::cout << "Client connected: " << client.GetAddress() << std::endl;

  client.Write("Hello!");
  std::cout << client.Read(0x1000) << std::endl;

  return 0;
}
