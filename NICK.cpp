#include "ircserv.hpp"

// Checking all connected clients to see if the Nickname is taken.
bool	isNicknameTaken(t_server *serv, std::string name)
{
	std::map<int, Client>::const_iterator it;

	for (it = serv->clientMap.begin(); it != serv->clientMap.end(); it++)
	{
		if (it->second.getNickname() == name)
			return (true);
	}
	return (false);
}

// Checking the Nickname to see if it is in a valid format
// Returns an empty string if no error was found
// Otherwise, returns an appropriate error message
const char *isNicknameValid(t_server *serv, std::string name)
{
	if (name.length() > 9 || name.length() == 0)
		return ("Error: Nickname should be 1-9 characters long.");
	else if (isdigit(name[0]) == true)
		return ("Error: Nickname should not start by a digit.");

	for (int i = 0; name[i]; i++)
	{
		if (isalnum(name[i]) == false && isInCharSet(name[i], "[]\\^{}_-") == false)
			return ("Error: Special characters in Nickname are limited to : []\\^{}_-");
	}

	if (isNicknameTaken(serv, name) == true)
		return ("Error: Nickname is already taken.");
	return (""); 
}

void	NICK(t_server *serv, int key, std::string arg)
{
	std::string msg;

	// If no error is found, set the client's Nickname to it's new value.
	if (strlen(isNicknameValid(serv, arg)) == 0)
	{
		serv->clientMap.find(key)->second.setNickname(arg);
		msg = "Nickname set to: " + arg + "\r\n";
		sendMsg(key, msg.c_str());
	}
	else // Otherwise, send an appropriate error message to the client.
	{
		msg = ":ircserv 433 * " + arg + " :" + isNicknameValid(serv, arg) + "\r\n";
		sendMsg(key, msg.c_str());
	}
	return ;
}
