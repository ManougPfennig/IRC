#include "ircserv.hpp"

void	PASS(t_server *serv, int key, std::string arg)
{
	// Send info msg if client has already entered password 
	if (serv->clientMap.find(key)->second.getPassed() == true)
	{
		sendMsg(key, "You have already entered the correct password.\n");
		return ;
	}
	// If the password is correct, set the client as passed. Otherwise send error message.
	if (arg == serv->password)
	{
		sendMsg(key, "Password is correct.\n");
		serv->clientMap.find(key)->second.SetPassed(true);
	}
	else
		sendMsg(key, "Password is incorrect.\n"s );
	return ;
}
