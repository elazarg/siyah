#include <iostream>
#include <libgen.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

std::string ProgramName;

void Die(std::string msg)
{
	std::cerr << ProgramName << ": error: " << msg << std::endl;
	_exit(1);
}

int main(int argc, char** argv)
{
	ProgramName = ::basename(argv[0]);

	int sockFd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (sockFd == -1)
		Die("Failed to open socket");


	

  return 0;
}
