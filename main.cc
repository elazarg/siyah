#include "server.h"

#include <iostream>
#include <libgen.h>

std::string ProgramName;

int main(int argc, char** argv)
{
  ProgramName = basename(argv[0]);

  TcpListener listener(1334);
  listener.Listen();

  auto client = listener.AcceptClient();
  std::cout << "Client connected" << std::endl;

  client.WriteLine("Hello!");
  std::cout << client.ReadLine() << std::endl;

  return 0;
}
