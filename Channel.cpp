#include "Channel.hpp"

// Construction and Destruction scripts

Channel::~Channel( void ) {}

Channel::Channel( void ) {}

Channel::Channel(const std::string &name) : _name(name) {}

Channel::Channel( const Channel &sa ) {}

// = Operator overcharge

Channel &Channel::operator=( const Channel &sa ) {

	return (*this);
}

// Getters and Setters

std::string	Channel::getName( void ) const{

	return (_name);
}

void		Channel::setName( std::string name){

	_name = name;
	return ;
}

std::vector<int>	&Channel::getClientsOfChannel() {
	return (_clients);
}

void				Channel::setPassword(std::string password) {
	_password = password;
	return ;
}

std::string			Channel::getPassword(void) const {
	return (_password);
}


//utils

void	Channel::addClientToChannel(int clientFd) {
	_clients.push_back(clientFd);
}

void	Channel::removeClientFromChannel(int clientFd) {
	for (std::vector<int>::iterator it = _clients.begin(); it != _clients.end(); it++){
		if (*it == clientFd){
			_clients.erase(it);
			return ;
		}
	}
}

bool	Channel::isClientInChannel(int clientFd) {
	for (std::vector<int>::iterator it = _clients.begin(); it != _clients.end(); it++){
		if (*it == clientFd){
			return (true);
		}
	}
	return (false);
}
