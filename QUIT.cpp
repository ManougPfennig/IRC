#include "ircserv.hpp"

void	QUIT(t_server *serv, int key, std::string arg)
{
	sendMsg(key, "Disconnecting from server...\n");
	serv->clientMap.erase(key);
	close(key);
}
