#include "server.h"

#include <iostream>
#include <libgen.h>

std::string ProgramName;

int main(int argc, char** argv)
{
  ProgramName = basename(argv[0]);

  ymarcov::net::TcpListener listener(1334);
  listener.Listen();

  auto client = listener.AcceptClient();
  std::cout << "Client connected" << std::endl;

  client.Write("Hello!");
  std::cout << client.Read(0x1000) << std::endl;

  return 0;
}
