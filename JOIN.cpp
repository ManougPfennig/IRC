#include "ircserv.hpp"

// Launch the join command, creates and/or join a channel, handles password or not, then broadcast corresponding messages
void	JOIN(t_server *serv, int clientFd, std::string channelName, std::string password) {

	// Checks first if the channel exists
	if (serv->channelMap.find(channelName) == serv->channelMap.end())
	{
		// If not, create a new channel
		serv->channelMap.insert(std::make_pair(channelName, Channel()));
		std::cout << channelName << " channel created." << std::endl;

		// Sets the specified password (if specified)
		if (!password.empty())
			serv->channelMap.find(channelName)->second.setPassword(password);

		// Adds the creator to the channel, as operator
		serv->channelMap[channelName].addClientToChannel(clientFd);
		serv->channelMap[channelName].addOperator(clientFd);
	}
	else if (!serv->channelMap.find(channelName)->second.getPassword().empty())
	{
		// If the channel already exist and is password protected, checks if the given password is correct
		if (serv->channelMap.find(channelName)->second.getPassword() == password)
		{
			// If password is correct, add the client to the channel
			serv->channelMap[channelName].addClientToChannel(clientFd);
			std::cout << clientFd << " joined the channel " << channelName << std::endl;

			// Send a confirmation message
			std::string	msg = "You joined " + channelName + "\n";
			sendMsg(clientFd, msg.c_str());
		}
		else
		{
			// If password is incorrect, send an error message
			sendMsg(clientFd, "Wrong password, please try again...\n");
			return ;
		}
	}
	else
	{
		// If the channel is not password protected, add the client to the channel
		serv->channelMap[channelName].addClientToChannel(clientFd);
		std::cout << clientFd << " joined the channel " << channelName << std::endl;

		// Send a confirmation message
		std::string	msg = "You joined " + channelName + "\n";
		sendMsg(clientFd, msg.c_str());
	}

	// If the client joined the channel successfully, broadcast a message to inform all other users on the channel
	broadcastJoining(serv, channelName, clientFd);
}
