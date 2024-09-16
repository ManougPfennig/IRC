#include "ircserv.hpp"

void	serverLoop( t_server &serv ) {

	while(1) {
		FD_ZERO(&serv.readfds);
		FD_ZERO(&serv.writefds);
		FD_ZERO(&serv.exceptfds);
		FD_SET(serv.serverSocket, &serv.readfds);
		FD_SET(serv.serverSocket, &serv.exceptfds);
		serv.max_fd = serv.serverSocket;
		for (int i = 0; i < MAXCLIENT; i++) {
			serv.client_socket_descriptor = client.getSocket(i);
			if (serv.client_socket_descriptor > 0)
				FD_SET(serv.client_socket_descriptor, &serv.readfds);
				FD_SET(serv.serverSocket, &serv.writefds);
				FD_SET(serv.serverSocket, &serv.exceptfds);
			if (serv.client_socket_descriptor > serv.max_fd)
				serv.max_fd = serv.client_socket_descriptor;
		}
		if (serv.activity = select(serv.max_fd + 1, &serv.readfds, &serv.writefds, &serv.exceptfds, NULL) < 0)
			throw (ServerActor::SelectFailed());
		else
			std::cout << "Activity detected." << std::endl;
		if (FD_ISSET(serv.serverSocket, &serv.readfds)) {
			serv.new_client = accept(serv.serverSocket, (struct sockaddr *)&serv.address6, (socklen_t *)&serv.addrlen);
			if (serv.new_client < 0) {
				perror("Something went wrong when connecting the new client...");
				exit(0);
			}
			for (int i = 0; i < MAXCLIENT; i++) {
				if (client.getSocket(i) == 0) {
					client.setSocket(i, serv.new_client);
					break;
				}
			}
		}
		for (int i = 0; i < MAXCLIENT; i++) {
			serv.client_socket_descriptor = client.getSocket(i);
			if (FD_ISSET(serv.client_socket_descriptor, &serv.exceptfds)) {
				std::cout << "Error on the " << serv.client_socket_descriptor << "th socket detected." << std::endl;
				close(serv.client_socket_descriptor);
				client.setSocket(i, 0);
				continue;
			}
			if (FD_ISSET(serv.client_socket_descriptor, &serv.readfds)) {
				if ((serv.valueread = read(serv.client_socket_descriptor, serv.buffer, 1024)) == 0) {
					getpeername(serv.client_socket_descriptor, (struct sockaddr *)&serv.address6, (socklen_t *)&serv.addrlen);
					char ip_str[INET6_ADDRSTRLEN];
					inet_ntop(AF_INET6, &(serv.address6.sin6_addr), ip_str, INET6_ADDRSTRLEN);
					std::cout << "Déconnexion de " << ip_str << ":" << ntohs(serv.address6.sin6_port) << std::endl;
					close(serv.client_socket_descriptor);
					client.setSocket(i, 0);
				}
				else {
					buffer[serv.valueread] = '\0';
					std::cout << "Message received : " << serv.buffer << std::endl;
					//donnes entrantes a gerer ici (parser commandes etc etc...)
				}
			}
			if (FD_ISSET(serv.client_socket_descriptor, &serv.writefds)) {
				//donnees sortantes a gerer ici
				//par exemple par un send(client_socket_descriptor, buff, len, flag (normalement mettre 0) );
			}
		}
	}
}