#include <iostream>

#include "tcp_listener.h"
#include "remote_client.h"

using ymarcov::net::TcpListener;
using ymarcov::net::RemoteClient;

int main(int argc, char** argv) {
	TcpListener listener(1335);
	listener.listen();

	RemoteClient client { listener.accept() };
	std::cout << "Client connected: " << client.address << std::endl;

	client.write("Hello!");
	std::cout << client.read(0x1000) << std::endl;

	return 0;
}
