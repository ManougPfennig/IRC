#include "ircserv.hpp"

bool	isNicknameTaken(t_server *serv, std::string name)
{
	std::map<int, Client>::const_iterator it;

	// Checking all connected clients to see if the Nickname is taken.
	for (it = serv->clientMap.begin(); it != serv->clientMap.end(); it++)
	{
		if (it->second.getNickname() == name)
			return (true);
	}
	return (false);
}

const char *isNicknameValid(t_server *serv, std::string name)
{
	if (name.length() > 9 || name.length() == 0)
		return ("Error: Nickname should be 1-9 characters long.\n");
	else if (isdigit(name[0]) == true)
		return ("Error: Nickname should not start by a digit.\n");

	for (int i = 0; name[i]; i++)
	{
		if (isalnum(name[i]) == false && isInCharSet(name[i], "[]\\^{}_-") == false)
			return ("Error: Special characters in Nickname are limited to : []\\^{}_-\n");
	}

	if (isNicknameTaken(serv, name) == true)
		return ("Error: Nickname is already taken.\n");
	return (""); 
}

void	NICK(t_server *serv, int key, std::string arg)
{
	std::string msg;

	// If no error is found, set the client's Nickname to it's new value.
	if (strlen(isNicknameValid(serv, arg)) == 0)
	{
		serv->clientMap.find(key)->second.setNickname(arg);
		msg = "Nickname set to: " + arg + "\n";
		sendMsg(key, msg.c_str());
	}
	else // Otherwise, send an appropriate error message to the client.
	{
		msg = isNicknameValid(serv, arg);
		sendMsg(key, msg.c_str());
	}
	return ;
}
