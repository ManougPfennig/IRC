#include "ircserv.hpp"

// — i : Définir/supprimer le canal sur invitation uniquement
// — t : Définir/supprimer les restrictions de la commande TOPIC pour les opérateurs de canaux
// — k : Définir/supprimer la clé du canal (mot de passe)
// — o : Donner/retirer le privilège de l’opérateur de canal
// — l : Définir/supprimer la limite d’utilisateurs pour le canal

bool	isArgUsable(std::string arg)
{
	// Checking if arg contains the minimum required amount of characters for call or a max of 3 different characters
	if (arg.size() < 2 || arg.size() > 4)
		return (false);

	// Checking that the first character is a sign
	if (arg[0] != '-' && arg[0] != '+')
		return (false);

	// Checking if the MODE character is valid
	for (int i = 1; arg[i]; i++) {
		if (isInCharSet(arg[i], "itkol") == false)
			return (false);
	}
	return (true);
}

void	MODE(t_server *serv, int clientFd, std::string channelName, std::string arg)
{
	// Checking if the specified channel exists
	if (doesChannelExist(serv, channelName) == false) {
		sendMsg(clientFd, "Error: Channel does not exist.\n");
		return ;
	}

	// Getting a reference to the specified channel
	Channel		&channel = serv->channelMap[channelName];

	// Checking if the caller is an operator
	if (channel.isOperator(clientFd) == false)
	{
		std::string msg = "Error: You are not operator in #" + channelName + "\r\n";
		sendMsg(clientFd, msg.c_str());
		return ;
	}

	// Keeping the MODE command type and it's sign (ex: +i or -k)
	std::string type = arg.substr(0, arg.find_first_of(' ', 0));
	if (!arg.empty())
		arg = arg.erase(0, arg.find_first_of(' ') + 1);

	// Checking if the command is called correctly
	if (isArgUsable(type) == false) {
		sendMsg(clientFd, "Error: MODE command, unvalid argument sent.\n");
		return ;
	}

	std::string commandList = "itkol";
	std::string	msg;
	char		sign = type[0];

	// Looping on all character types sent and applying their logic accordingly
	for (int i = 1; type[i]; i++) {

		// Using a switch by getting the type of command as an index of commandList
		switch (commandList.find_first_of(type[i], 0))
		{
			case 0: // i (invite only)
			{
				if (sign == '+') {
					channel.setIsInviteOnly(true);
					msg = "#" + channelName + ": set to invite only.\r\n";
					sendMsg(clientFd, msg.c_str());
				}
				else {
					channel.setIsInviteOnly(false);
					msg = "#" + channelName + ": disabled invite only.\r\n";
					sendMsg(clientFd, msg.c_str());
				}
				break ;
			}
			case 1: // t (topic restriction)
			{
				if (sign == '+') {
					channel.setTopicSettableByUsers(false);
					msg = "#" + channelName + ": topic can now only be set by operators.\r\n";
					sendMsg(clientFd, msg.c_str());
				}
				else {
					channel.setTopicSettableByUsers(true);
					msg = "#" + channelName + ": topic can now be set by anyone.\r\n";
					sendMsg(clientFd, msg.c_str());
				}
				break ;
				
			}
			case 2: // k (password settings)
			{
				if (sign == '+') {
					channel.setPassword(arg);
					msg = "#" + channelName + ": password set successfully.\r\n";
					sendMsg(clientFd, msg.c_str());
				}
				else {
					channel.setPassword("");
					msg = "#" + channelName + ": password removed successfully.\r\n";
					sendMsg(clientFd, msg.c_str());
				}
				break ;
			}
			case 3: // o (operator privilege)
			{
				// Checking if the specified target exists
				if (gC(serv, arg) == -1) {
					msg = "#" + channelName + ": '" + arg + "' user not found.\r\n";
					sendMsg(clientFd, msg.c_str());
					break ;
				}
				if (sign == '+') {
					channel.addOperator(gC(serv, arg));
					msg = "#" + channelName + ": '" + arg + "' added to operator list.\r\n";
					sendMsg(clientFd, msg.c_str());
				}
				else {
					channel.removeOperator(gC(serv, arg));
					msg = "#" + channelName + ": '" + arg + "' removed from operator list.\r\n";
					sendMsg(clientFd, msg.c_str());
					msg = "#" + channelName + ": you have been removed from operator list.\r\n";
					sendMsg(gC(serv, arg), msg.c_str());
				}
				break ;
			}
			case 4: // l (number of users)
			{
				if (sign == '+') {
					if (channel.setUsersLimit(arg) != ERROR) {
						channel.setHasUserLimit(true);
						msg = "#" + channelName + ": limit on number of users set to " + std::to_string(channel.getUsersLimit()) + "\r\n";
					}
					else
						msg = "#" + channelName + ": Invalid input on max number of users, settings remain unchanged.\r\n";
					sendMsg(clientFd, msg.c_str());
				}
				else {
					channel.setHasUserLimit(false);
					msg = "#" + channelName + ": removed limit on number of users.\r\n";
					sendMsg(clientFd, msg.c_str());
				}
				break ;
			}
		}
	}
	return ;
}
