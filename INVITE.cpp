#include "ircserv.hpp"

// Send a confirmation message to client
// Send an information message to target

bool	isUsernameValid(std::string	name)
{
	if (name.length() > 10 || name.length() == 0)
		return (false);

	for (int i = 0; name[i]; i++)
	{
		if (isalnum(name[i]) == false && isInCharSet(name[i], "-./:_") == false)
			return (false);
	}
	return (true);
}

void	INVITE( t_server *serv, int clientFd, std::string username, std::string arg )
{
	std::string msg;

	// Checking if the target's username is valid
	if (isUsernameValid(username) == false) {
		msg = "Error: Specified username '" + username + "' is invalid.\r\n";
		sendMsg(clientFd, msg.c_str());
		return ;
	}
	
	// Checking if the target exists
	if (isUsernameTaken(serv, username) == false) {
		msg = "Error: '" + username + "' no such user in server.\r\n";
		sendMsg(clientFd, msg.c_str());
	}

	// Checking if the channel name is not empty
	if (arg.empty() || (arg[0] == '#' && arg.size() == 1)) {
		msg = "Error: Please specify a channel name.\r\n";
		sendMsg(clientFd, msg.c_str());
	}

	// Checking if the channel name is preceded by an '#' for format, then removing it
	if (arg[0] == '#')
		arg.erase(0, 1);
	else {
		msg = "Error: Please preced the channel's name with a '#'.\r\n";
		sendMsg(clientFd, msg.c_str());
	}

	// Checking if the channel exists, then get a reference to it
	if (doesChannelExist(serv, arg) == false) {
		msg = "Error: '#" + arg + "' no such channel in server.\r\n";
		sendMsg(clientFd, msg.c_str());
	}
	Channel	&channel = serv->channelMap[arg];

	// Checking if client is in the channel
	if (channel.isClientInChannel(clientFd) == false) {
		msg = "Error: '#" + arg + "' you are not in this channel.\r\n";
		sendMsg(clientFd, msg.c_str());
	}

	// Checking if the target is already in the channel
	if (channel.isClientInChannel(gC(serv, username)) == true) {
		msg = "Error: user '" + username + "' is already in #" + arg +".\r\n";
		sendMsg(clientFd, msg.c_str());
	}

	// Adding the target to the channel's invite list
	channel.addToInviteList(username);
	
	// Message client that the invite has been sent successfully
	msg = "#" + arg + ": user '" + username + "' has been invited.\r\n";
	sendMsg(clientFd, msg.c_str());

	// Send a formatted message to the target to inform of the invitation
	Client &client = gC(serv, clientFd);
	msg = ":" + client.getUsername() + "!" + client.getNickname() + "@ircserv INVITE " + username + " #" + arg + "\r\n";
	sendMsg(gC(serv, username), msg.c_str());
	return ;
}
