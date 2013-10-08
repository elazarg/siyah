#include <iostream>

#include "tcp_listener.h"
#include "remote_client.h"

using newnet::TcpListener;
using newnet::RemoteClient;

using std::cout;
using std::endl;

int main(int argc, char** argv) {
	int port = argc > 1 ? std::stoi(argv[1]) : 1335;

	TcpListener listener(port);
	listener.listen();

	cout << "Listening on port "  << port << endl;

	RemoteClient client { listener.accept() };
	cout << "Client connected: " << client.address << endl;

	client.write("Hello!\n");
	cout << client.read(0x1000) << endl;
}
