#include "ircserv.hpp"
#include "Client.hpp"

void	openServer( ServerActor &serv, char *port, char *password )
{
	fd_set				readfds, writefds, exceptfds;
	struct sockaddr_in6	address6;
	char				buffer[BUFFERSIZE];
	Client				client;
	int					server_fd, client_socket_descriptor, max_fd, activity, new_client, valueread;

	// Set server port
	serv.setPort(atoi(port));

	// Set password
	serv.setPassword(password);

	serv.setServerSocket(socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP));
	if (serv.getServerSocket() < 0)
		throw (ServerActor::SocketCreationFailed());
	else
		std::cout << "Server socket created." << std::endl;
	std::cout << "debug:" << server_fd << std::endl;
	client.initSocket();
	address6.sin6_family = AF_INET6;
	address6.sin6_addr = in6addr_any;
	address6.sin6_port = htons(serv.getPort());
	if (bind(serv.getServerSocket(), (struct sockaddr *)&address6, sizeof(address6)) < 0)
		throw (ServerActor::SocketBindingFailed());
	else
		std::cout << "Server socket binded." << std::endl;
	if (listen(serv.getServerSocket(), MAXCLIENT) < 0)
		throw (ServerActor::SocketListeningFailed());
	else
		std::cout << "Server socket is now listening." << std::endl;
	int addrlen = sizeof(address6);
	serverLoop(client_socket_descriptor,);
	close(serv.getServerSocket());
	return ;
}
