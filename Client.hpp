#ifndef CLIENT_HPP
# define CLIENT_HPP

# define MAXCLIENT 10

#include "ircserv.hpp"
#include "ServerActor.hpp"

class Client {
	private:

	public:

		~Client();
		Client();
		Client(const Client &sa);
		Client &operator=(const Client &sa);

		int		getSocket(int i) const;
		void	setSocket(int i, int socket);
		void	initSocket();

};

#endif