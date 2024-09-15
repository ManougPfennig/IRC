#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "ServerActor.hpp"
#include "ircserv.hpp"

class Client {
	private:
		int	_clientSocket[MAXCLIENT];

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