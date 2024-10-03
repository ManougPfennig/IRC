#include "ircserv.hpp"

//remove the client from all the channels he were still in when disconnecting
void	cleanChannelsFromDisconnectingClients(t_server *serv, int clientFd) {

	Client &client = gC(serv, clientFd);
	for (std::map<std::string, Channel>::iterator it = serv->channelMap.begin(); it != serv->channelMap.end(); it++) {
		//remove the client from every channels that exist because removeClientFromChannel() already check if he's in it
		it->second.removeClientFromChannel(clientFd);
		//departure message to other users in the channel
		broadcastLeaving(serv, it->second.getName(), clientFd, "");
		//remove that disconnecting client from the invitation list of that channel
		it->second.removeFromInviteList(client.getUsername());
		//close channel if it got emptied by that departure
		if (it->second.getClientsOfChannel().empty()) {
			std::cout << "The channel '" << it->second.getName() << "' was empty so it got closed." << std::endl;
			serv->channelMap.erase(it->second.getName());
		}
	}
}
