#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "ServerActor.hpp"

class Client {
	private:

	public:

		~Client();
		Client();
		Client(const Client &sa);
		Client &operator=(const Client &sa);

};

#endif