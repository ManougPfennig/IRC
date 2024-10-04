#include "ircserv.hpp"

// Returns an empty string if no error was found.
// Otherwise, returns an appropriate error message.
std::string	isValidChannelName( std::string name ) {

	std::string msg;

	if (name.size() > 50)
		return ("name is over 50 characters long");
	
	if (name.empty())
		return ("name is empty");

	for (int i = 0; name[i]; i++) {
		if (isalnum(name[i]) == 0 && isInCharSet(name[i], "-_&#") == false) {
			msg = "'" + name.substr(i, 1) + "' is not a usable character";
			return (msg);
		}
	}
	return ("");
}

// Launch the join command, creates and/or join a channel, handles password or not, then broadcast corresponding messages
void	JOIN(t_server *serv, int clientFd, std::string channelName, std::string password) {

	std::string	msg;

	// If the channel doesn't already exists, it is created and the function stops here.
	if (serv->channelMap.find(channelName) == serv->channelMap.end())
	{

		// Checks if the channel name is usable or send an appropriate error message to the client
		if (!isValidChannelName(channelName).empty()) {
			msg = "Error: '" + channelName + "' : " + isValidChannelName(channelName) + ".\r\n";
			sendMsg(clientFd, msg.c_str());
			return ;
		}

		// Creating a new channel
		serv->channelMap.insert(std::make_pair(channelName, Channel()));
		std::cout << channelName << " channel created." << std::endl;

		// If specified, set the given password
		if (!password.empty())
			serv->channelMap.find(channelName)->second.setPassword(password);

		// Adds the creator to the channel and as channel operator
		serv->channelMap[channelName].addClientToChannel(clientFd);
		serv->channelMap[channelName].addOperator(clientFd);
		broadcastJoining(serv, channelName, clientFd);

		return ;
	}

	// Getting a reference to the specified channel
	Channel	&channel = serv->channelMap[channelName];

	// If the channel is password protected and the password is incorrect, decline the join request
	if (!channel.getPassword().empty() && channel.getPassword() != password) {
		msg = "#" + channelName + " : Password is incorrect.\r\n";
		sendMsg(clientFd, msg.c_str());
		return ;
	}

	// If the channel has a user limit and is already full, decline the join request
	if (channel.getHasUserLimit() == true && channel.getUsersLimit() >= channel.getClientsOfChannel().size()) {
		msg = "#" + channelName + " : Channel is full.\r\n";
		sendMsg(clientFd, msg.c_str());
		return ;
	}

	// If the channel is on invite only and the client is not invited, decline the join request
	if (channel.getIsInviteOnly() == true && channel.isInInviteList(gC(serv, clientFd).getUsername()) == false) {
		msg = "#" + channelName + " : Channel is invite only.\r\n";
		sendMsg(clientFd, msg.c_str());
		return ;
	}

	// Adding the client to the channel and sending a confirmation message
	serv->channelMap[channelName].addClientToChannel(clientFd);
	msg = "You joined #" + channelName + "\r\n";
	sendMsg(clientFd, msg.c_str());

	// Broadcasting a message to inform all other users of the new member
	broadcastJoining(serv, channelName, clientFd);

	return ;
}
