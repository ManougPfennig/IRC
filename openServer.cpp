#include "ircserv.hpp"

void	openServer( ServerActor &serv )
{
	serv.setSocket(socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP));
	if (serv.getSocket() < 0)
		throw (ServerActor::SocketCreationFailed());
	else
		std::cout << "Server socket created" << std::endl;
	return ;
}
