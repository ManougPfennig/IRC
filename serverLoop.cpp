		// for (int i = 0; i < MAXCLIENT; i++) {
		// 	it->first = client.getSocket(i);
		// 	if (it->first > 0)
		// 		FD_SET(it->first, &serv->readfds);
		// 		FD_SET(serv->serverSocket, &serv->writefds);
		// 		FD_SET(serv->serverSocket, &serv->exceptfds);
		// 	if (it->first > serv->nfds)
		// 		serv->nfds = it->first;
		// }


#include "ircserv.hpp"

void	serverLoop( t_server *serv ) {

	std::map<int, Client>::const_iterator	it;
	std::vector<int>						clientsToRemove;

	while (1)
	{
		FD_ZERO(&serv->readfds);
		FD_ZERO(&serv->writefds);
		FD_ZERO(&serv->exceptfds);
		FD_SET(serv->serverSocket, &serv->readfds);
		FD_SET(serv->serverSocket, &serv->exceptfds);

		// Setting highest Fd to the serverSocket Fd by default
		serv->nfds = serv->serverSocket;
		for (it = serv->clientMap.begin(); it != serv->clientMap.end(); it++)
		{
			
			// Adding each client Fd to the Fd_Set
			FD_SET(it->first, &serv->readfds);

			// nfds should set to the highest client fd value in the clientMap
			if (it->first > serv->nfds)
				serv->nfds = it->first;
		}

		// Waiting for any incoming activity
		if (serv->activity = select(serv->nfds + 1, &serv->readfds, &serv->writefds, &serv->exceptfds, NULL) < 0)
			throw (ServerException::SelectFailed());
		else
			std::cout << "Activity detected." << std::endl;

		// Checking if activity is a connexion request from a new client
		if (FD_ISSET(serv->serverSocket, &serv->readfds))
		{
			try
			{
				serv->new_client = accept(serv->serverSocket, (struct sockaddr *)&serv->address6, (socklen_t *)&serv->addrlen);
				if (serv->new_client < 0)
					throw (ServerException::ClientAcceptFailed());
				// If connexion is accepted successfully, the new client Fd is associated with a new Client instance and added to clientMap
				serv->clientMap.insert(std::make_pair(serv->new_client, Client()));
				// set the client socket fd as non-blocking
				std::cout << "New connexion...\n";
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
		}

		// Checking if activity is an error from a client fd
		for (it = serv->clientMap.begin(); it != serv->clientMap.end(); it++)
		{
			if (FD_ISSET(it->first, &serv->exceptfds))
			{
				// If an error occured, removing the client for the server and closing the client Fd
				std::cout << "Error on the client associated with fd " << it->first << "." << std::endl;
				clientsToRemove.push_back(it->first);
			}
		}

		// Checking if activity is an incoming message or deconnexion signal
		for (it = serv->clientMap.begin(); it != serv->clientMap.end(); it++)
		{
			if (FD_ISSET(it->first, &serv->readfds))
			{
				// If read() returns 0, client is disconnecting and associated data is cleaned
				if ((serv->valueread = read(it->first, serv->buffer, BUFFERSIZE - 1)) == 0)
				{
					// Displaying which client has disconnected
					char ip_str[INET6_ADDRSTRLEN];
					getpeername(it->first, (struct sockaddr *)&serv->address6, (socklen_t *)&serv->addrlen);
					inet_ntop(AF_INET6, &(serv->address6.sin6_addr), ip_str, INET6_ADDRSTRLEN);
					std::cout << "Déconnexion de " << ip_str << ":" << ntohs(serv->address6.sin6_port) << std::endl;
					clientsToRemove.push_back(it->first);
				}
				// DO NOT DELETE THIS
				// else if (strstr(serv->buffer, "\r\n")) {
				// 	serv->buffer[serv->valueread] = '\0';
                // 	std::cout << "Complete message received: " << serv->buffer << std::endl;
            	// }
				else
				{
					// If read() returns a value higher than 0, the message sent by the client will be interpreted
					serv->buffer[serv->valueread] = '\0';
					if (it->second.getRegistered() == false)
						registerNewClient(serv, it->first);
					// messageParsing(serv);
				}
			}
			if (FD_ISSET(it->first, &serv->writefds))
			{
				//donnees sortantes a gerer ici
				//par exemple par un send(client_socket_descriptor, buff, len, flag (normalement mettre 0) );
			}
		}
		// Removing clients that has disconnected
		for (std::vector<int>::const_iterator rm = clientsToRemove.begin(); rm != clientsToRemove.end(); rm++)
		{
			serv->clientMap.erase(*rm);
			close(*rm);
		}
		clientsToRemove.clear();
	}
}
