#include "ircserv.hpp"

void	serverLoop(ServerActor &serv) {
	while(1) {
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);
		FD_ZERO(&exceptfds);
		FD_SET(serv.getServerSocket(), &readfds);
		FD_SET(serv.getServerSocket(), &exceptfds);
		max_fd = serv.getServerSocket();
		for (int i = 0; i < MAXCLIENT; i++) {
			client_socket_descriptor = client.getSocket(i);
			if (client_socket_descriptor > 0)
				FD_SET(client_socket_descriptor, &readfds);
				FD_SET(serv.getServerSocket(), &writefds);
				FD_SET(serv.getServerSocket(), &exceptfds);
			if (client_socket_descriptor > max_fd)
				max_fd = client_socket_descriptor;
		}
		if (activity = select(max_fd + 1, &readfds, &writefds, &exceptfds, NULL) < 0)
			throw (ServerActor::SelectFailed());
		else
			std::cout << "Activity detected." << std::endl;
		if (FD_ISSET(serv.getServerSocket(), &readfds)) {
			new_client = accept(serv.getServerSocket(), (struct sockaddr *)&address6, (socklen_t *)&addrlen);
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
}