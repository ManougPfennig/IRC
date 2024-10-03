#include "ircserv.hpp"

// When called, kicks the specified user from the channel (only if caller has operator rights)
void	KICK(t_server *serv, int clientFd, std::string channelName, std::string arg)
{
	Channel		&channel = serv->channelMap[channelName];

	// Checking if the specified channel exists
	if (doesChannelExist(serv, channelName) == false) {
		sendMsg(clientFd, "Error: Channel does not exist.\n");
		return ;
	}

	// Checks if the caller is an operator
	if (channel.isOperator(clientFd) == false)
	{
		std::string msg = "Error: You are not operator in #" + channelName + "\r\n";
		sendMsg(clientFd, msg.c_str());
		return ;
	}

	// Storing the specifed target's name and it's associated fd, then removing it from arg
	std::string	target;
	int			targetFd;
	if (contains(arg, ' ') == true) {
		target = arg.substr(0, arg.find_first_of(' '));
		arg = arg.erase(0, target.size() + 1);
	}
	else {
		target = arg;
		arg.clear();
	}
	targetFd = gC(serv, target);

	// Checks if the target exists and/or is in the channel
	if (targetFd == -1 || channel.isClientInChannel(targetFd) == false)
	{
		std::string msg = "Error: No such user in #" + channelName + "\r\n";
		sendMsg(clientFd, msg.c_str());
		return ;
	}

	// Checks if the target is an operator (cannot be kicked)
	if (channel.isOperator(targetFd) == true)
	{
		std::string msg = "Error: Cannot kick another operator.\r\n";
		sendMsg(clientFd, msg.c_str());
		return ;
	}

	// Keeping only the reason of the kick
	if (!arg.empty() && arg[0] == ':')
		arg.erase(0, 1);

	// Broadcasting the message in the channel kicking target from the channel
	broadcastKick(serv, channelName, clientFd, targetFd, arg);
	channel.removeClientFromChannel(targetFd);
	return ;
}