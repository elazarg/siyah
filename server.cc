#include <iostream>
#include <libgen.h>
#include <sys/types.h>
#include <sys/socket.h>

std::string ProgramName;

void Die(std::string msg)
{
	std::cerr << ProgramName << ": error: " << msg << std::endl;
}

int main(int argc, char** argv)
{
	ProgramName = ::basename(argv[0]);

	int sockFd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (sockFd == -1)
		Die("Failed to open socket");


	

  return 0;
}
