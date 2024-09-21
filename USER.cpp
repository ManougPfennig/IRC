#include "ircserv.hpp"


// Checking if the Username is valid and can be used.
// (length, characters type and if it's taken)
const char	*isUsernameValid(std::string name)
{
	if (name.length() > 10 || name.length() == 0)
		return ("Error: Username should be 1-10 characters long.\n");

	for (int i = 0; name[i]; i++)
	{
		if (isalnum(name[i]) == false && isInCharSet(name[i], "-./:_") == false)
			return ("Error: Special characters in Username are limited to : -./:_\n");
	}

	return (""); 
}

void	USER(t_server *serv, int key, std::string arg)
{
	std::string msg;


	arg = arg.substr(0, arg.find_first_of(' '));
	// Checks if client already has a username
	if (serv->clientMap.find(key)->second.getUsername().length() > 0)
	{
		sendMsg(key, "Once set, Username cannot be changed.\n");
	}
	else if (strlen(isUsernameValid(arg)) == 0)
	{
		// If no error is found, set the client's Username to it's new value.
		serv->clientMap.find(key)->second.setUsername(arg);
		msg = "Username set to: " + arg + "\n";
		sendMsg(key, msg.c_str());
	}
	else
	{
		// Otherwise, send an appropriate error message to the client.
		msg = isUsernameValid(arg);
		sendMsg(key, msg.c_str());
	}
	return ;
}
