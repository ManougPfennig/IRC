#include "ircserv.hpp"
#include "Client.hpp"

void	openServer( t_server &serv, char *port, char *password )
{

	// Set server port
	serv.port = (atoi(port));

	// Set password
	serv.password = password;

	// Open server socket
	serv.serverSocket = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
	if (serv.serverSocket < 0)
		throw (ServerActor::SocketCreationFailed());
	else
		std::cout << "Server socket created." << std::endl;
	std::cout << "debug:" << serv.server_fd << std::endl;

	// Set address and port for server socket
	serv.address6.sin6_family = AF_INET6;
	serv.address6.sin6_addr = in6addr_any;
	serv.address6.sin6_port = htons(serv.port);
	if (bind(serv.serverSocket, (struct sockaddr *)&serv.address6, sizeof(serv.address6)) < 0)
		throw (ServerActor::SocketBindingFailed());
	else
		std::cout << "Server socket binded." << std::endl;

	// Start listening on the server socket
	if (listen(serv.serverSocket, MAXCLIENT) < 0)
		throw (ServerActor::SocketListeningFailed());
	else
		std::cout << "Server socket is now listening." << std::endl;

	serv.addrlen = sizeof(serv.address6);
	serverLoop(serv);
	close(serv.serverSocket);
	return ;
}
