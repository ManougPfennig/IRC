#include "ircserv.hpp"

//remove the client from all the channels he were still in when disconnecting
void	cleanChannelsFromDisconnectingClients(t_server *serv, int clientFd) {
	for (std::map<std::string, Channel>::iterator it = serv->channelMap.begin(); it != serv->channelMap.end(); it++) {
		//remove the client from every channels that exist because removeClientFromChannel() already check if he's in it
		it->second.removeClientFromChannel(clientFd);
	}
}
