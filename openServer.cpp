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

	//cette partie ne semble pas forcement utile pour moi, mais si tu en as besoin, decommente ^^

	// serv.setServerSocket(socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP));
	// if (serv.getServerSocket() < 0)
	// 	throw (ServerActor::SocketCreationFailed());
	// else
	// 	std::cout << "Server socket created." << std::endl;

	server_fd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
	std::cout << "debug:" << server_fd << std::endl;
	client.initSocket();
	address6.sin6_family = AF_INET6;
	address6.sin6_addr = in6addr_any;
	address6.sin6_port = htons(serv.getPort());
	if (bind(server_fd, (struct sockaddr *)&address6, sizeof(address6)) < 0)
		throw (ServerActor::SocketBindingFailed());
	else
		std::cout << "Server socket binded." << std::endl;
	if (listen(server_fd, MAXCLIENT) < 0)
		throw (ServerActor::SocketListeningFailed());
	else
		std::cout << "Server socket is now listening." << std::endl;
	int addrlen = sizeof(address6);
	close(server_fd); //ATTENTION!!! a enlever si on veut tester le code en dessous d'ici
	while(1) {
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);
		FD_ZERO(&exceptfds);
		FD_SET(server_fd, &readfds);
		FD_SET(server_fd, &exceptfds);
		max_fd = server_fd;
		for (int i = 0; i < MAXCLIENT; i++) {
			client_socket_descriptor = client.getSocket(i);
			if (client_socket_descriptor > 0)
				FD_SET(server_fd, &readfds);
				FD_SET(server_fd, &writefds);
				FD_SET(server_fd, &exceptfds);
			if (client_socket_descriptor > max_fd)
				max_fd = client_socket_descriptor;
		}
		if (activity = select(max_fd + 1, &readfds, &writefds, &exceptfds, NULL) < 0)
			throw (ServerActor::SelectFailed());
		else
			std::cout << "Activity detected." << std::endl;
		if (FD_ISSET(server_fd, &readfds)) {
			new_client = accept(server_fd, (struct sockaddr *)&address6, (socklen_t *)&addrlen);
			if (new_client < 0) {
				perror("Something went wrong when connecting the new client...");
				exit(0);
			}
			for (int i = 0; i < MAXCLIENT; i++) {
				if (client.getSocket(i) == 0) {
					client.setSocket(i, new_client);
					break;
				}
			}
		}
		for (int i = 0; i < MAXCLIENT; i++) {
			client_socket_descriptor = client.getSocket(i);
			if (FD_ISSET(client_socket_descriptor, &exceptfds)) {
				std::cout << "Error on the " << client_socket_descriptor << "th socket detected." << std::endl;
				close(client_socket_descriptor);
				client.setSocket(i, 0);
				continue;
			}
			if (FD_ISSET(client_socket_descriptor, &readfds)) {
				if ((valueread = read(client_socket_descriptor, buffer, 1024)) == 0) {
					getpeername(client_socket_descriptor, (struct sockaddr *)&address6, (socklen_t *)&addrlen);
					char ip_str[INET6_ADDRSTRLEN];
					inet_ntop(AF_INET6, &(address6.sin6_addr), ip_str, INET6_ADDRSTRLEN);
					std::cout << "Déconnexion de " << ip_str << ":" << ntohs(address6.sin6_port) << std::endl;
					close(client_socket_descriptor);
					client.setSocket(i, 0);
				}
				else {
					buffer[valueread] = '\0';
					std::cout << "Message received : " << buffer << std::endl;
					//donnes entrantes a gerer ici (parser commandes etc etc...)
				}
			}
			if (FD_ISSET(client_socket_descriptor, &writefds)) {
				//donnees sortantes a gerer ici
				//par exemple par un send(client_socket_descriptor, buff, len, flag (normalement mettre 0) );
			}
		}
	}
	return ;
}
