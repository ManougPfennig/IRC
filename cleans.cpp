#include "ircserv.hpp"

//remove the client from all the channels he were still in when disconnecting
void	cleanChannelsFromDisconnectingClients(t_server *serv, int clientFd) {

	Client &client = gC(serv, clientFd);
	std::vector<std::string>	emptyChannels;

	for (std::map<std::string, Channel>::iterator it = serv->channelMap.begin(); it != serv->channelMap.end(); it++) {
		//remove the client from every channels that exist because removeClientFromChannel() already check if he's in it
		it->second.removeClientFromChannel(clientFd);
		//departure message to other users in the channel
		broadcastLeaving(serv, it->second.getName(), clientFd, "");
		//remove that disconnecting client from the invitation list of that channel
		it->second.removeFromInviteList(client.getUsername());
		//get the list of channels that are now empty
		if (it->second.getClientsOfChannel().empty()) {
			emptyChannels.push_back(it->second.getName());
		}
	}
	//close empty channels
	for (std::vector<std::string>::iterator ite = emptyChannels.begin(); ite != emptyChannels.end(); ite++) {
		serv->channelMap.erase(*ite);
	}
}
