#include "ircserv.hpp"

// Parses the command sent and launch the action needed 
void	cmdsParse(t_server *serv, int clientFd, std::string toParse) {

	// Keeping the command from the input string
	std::string	command = toParse.substr(0, toParse.find_first_of(' '));
	toParse.erase(0, toParse.find_first_of(' ') + 1);

	// Removing any \r\n from the end of the string
	toParse = toParse.substr(0, std::min(toParse.find_first_of('\r'), toParse.find_first_of('\n')));

	// Keeping the channel from the input string and removing it from toParse
	std::string	channelName = toParse.substr(0, toParse.find_first_of(' '));
	if (contains(toParse, ' '))
		toParse.erase(0, toParse.find_first_of(' ') + 1);
	else
		toParse.clear();

	// Keeping the argument from the input string
	std::string	arg = toParse;
	if (arg[0] == ':')
		arg.erase(0, 1);

	// Switching on the specified command
	switch (whichCommand(command))
	{
		case 4: // JOIN
		{
			// Checking if the channel name is formatted correctly
			if (channelName.empty() || channelName[0] != '#') {
				sendMsg(clientFd, "Error: invalid channel name provided.\r\n");
				break ;
			}
			else
				channelName.erase(0, 1);

			if (!channelName.empty())
				JOIN(serv, clientFd, channelName, arg);
			else
				sendMsg(clientFd, "Error: no channel name provided.\r\n");
			break ;
		}
		case 5: // PART
		{
			// Checking if the channel name is formatted correctly
			if (channelName.empty() || channelName[0] != '#') {
				sendMsg(clientFd, "Error: invalid channel name provided.\r\n");
				break ;
			}
			else
				channelName.erase(0, 1);

			if (!channelName.empty())
				PART(serv, clientFd, channelName, arg);
			else
				sendMsg(clientFd, "Error: no channel name provided.\r\n");
			break ;
		}
		case 6: // PRIVMSG
		{
			if (channelName[0] == '#') { // Interpret as message to channel
				channelName.erase(0, 1);
				if (!channelName.empty())
					broadcastToChannel(serv, channelName, clientFd, arg);
				else
					sendMsg(clientFd, "Error: no channel name provided.\r\n");
			}
			else // Interpret as message to user
				sendPrivateMessage(serv, channelName, clientFd, arg);
			break ;
		}
		case 7: // KICK
		{
			// Checking if the channel name is formatted correctly
			if (channelName.empty() || channelName[0] != '#') {
				sendMsg(clientFd, "Error: invalid channel name provided.\r\n");
				break ;
			}
			else
				channelName.erase(0, 1);

			if (!channelName.empty())
				KICK(serv, clientFd, channelName, arg);
			else
				sendMsg(clientFd, "Error: no channel name provided.\r\n");
			break;
		}
		case 8: // MODE
		{
			// Checking if the channel name is formatted correctly
			if (channelName.empty() || channelName[0] != '#') {
				sendMsg(clientFd, "Error: invalid channel name provided.\r\n");
				break ;
			}
			else
				channelName.erase(0, 1);

			if (!channelName.empty())
				MODE(serv, clientFd, channelName, arg);
			else
				sendMsg(clientFd, "Error: no channel name provided.\r\n");
			break;
		}
		case 9: // INVITE
		{
			// Invite's format starts with the username then the channel, unlike EVERY other command
			if (!channelName.empty()) // channelName is actually, in this case, the username
				INVITE(serv, clientFd, channelName, arg);
			else {
				sendMsg(clientFd, "Error: no username provided.\r\n");
				break ;
			}
			break;
		}
		case 10: //TOPIC
		{
			// Checking if the channel name is formatted correctly
			if (channelName.empty() || channelName[0] != '#') {
				sendMsg(clientFd, "Error: invalid channel name provided.\r\n");
				break ;
			}
			else
				channelName.erase(0, 1);

			//check if there's still something in channelName after removing '#'
			if (!channelName.empty())
				TOPIC(serv, clientFd, channelName, arg);
			else
				sendMsg(clientFd, "Error: no channel name provided.\r\n");
			break;
		}
		case 11: // QUIT
		{
			gC(serv, clientFd).setQuit(true);
			break ;
		}
		case -1:
		{
			sendMsg(clientFd, "Invalid command sent.\n");
			break;
		}
	}
	return ;
}
