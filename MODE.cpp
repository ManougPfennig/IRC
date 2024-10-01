#include "ircserv.hpp"


// MODE #Finnish +o Kilroy         ; Command to give 'chanop' privileges
//                                to Kilroy on channel #Finnish.

// MODE #Finnish +v Wiz            ; Command to allow WiZ to speak on
//                                #Finnish.

// MODE #Fins -s                   ; Command to remove 'secret' flag
//                                from channel #Fins.

// MODE #42 +k oulu                ; Command to set the channel key to
//                                "oulu".

// MODE #42 -k oulu                ; Command to remove the "oulu"
//                                channel key on channel "#42".

// — i : Définir/supprimer le canal sur invitation uniquement
// — t : Définir/supprimer les restrictions de la commande TOPIC pour les opérateurs de canaux
// — k : Définir/supprimer la clé du canal (mot de passe)
// — o : Donner/retirer le privilège de l’opérateur de canal
// — l : Définir/supprimer la limite d’utilisateurs pour le canal

bool	isArgUsable(std::string arg)
{
	// Checking if arg contains the minimum required amount of characters for call
	if (arg.size() < 2)
		return (false);

	// Checking that the first character is a sign
	if (arg[0] != '-' && arg[0] != '+')
		return (false);

	// Checking if the MODE character is valid
	if (isInCharSet(arg[1], "itkol") == false)
		return (false);
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

	// Removing the \r\n at the end of arg
	arg = arg.substr(0, std::min(arg.find_first_of('\r'), arg.find_first_of('\n')));

	// Checking if the command is called correctly
	if (isArgUsable(arg) == false) {
		sendMsg(clientFd, "Error: MODE command, unvalid argument sent.\n");
		return ;
	}

	std::string commandList = "itkol";
	switch (commandList.find_first_of(arg[1], 0))
	{
		case 0: // i (invite only)
		{
			break ;
		}
		case 1: // t (topic restriction)
		{
			break ;
			
		}
		case 2: // k (password settings)
		{
			break ;
			
		}
		case 3: // o (operator privilege)
		{
			break ;
			
		}
		case 4: // l (number of users)
		{
			break ;
			
		}
	}
}