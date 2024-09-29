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

void				Channel::setTopic(std::string topic) {

	_topic = topic;
	return ;
}

std::string			Channel::getTopic(void) const {

	return (_topic);
}


//utils

void	Channel::addClientToChannel(int clientFd) {

	_clients.push_back(clientFd);
	return ;
}

void	Channel::removeClientFromChannel(int clientFd) {

	// remove from _clients
	for (std::vector<int>::iterator it = _clients.begin(); it != _clients.end(); it++){
		if (*it == clientFd){
			_clients.erase(it);
			return ;
		}
	}

	// remove from _operators
	for (std::vector<int>::iterator it = _operators.begin(); it != _operators.end(); it++){
		if (*it == clientFd){
			_operators.erase(it);
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

// Adds this client to the channel's operator list
void	Channel::addOperator(int clientFd) {

	_operators.push_back(clientFd);
	return ;
}

// Removes this client to the channel's operator list
void	Channel::removeOperator(int clientFd) {

	for (std::vector<int>::const_iterator it = _operators.begin(); it != _operators.end(); it++)
	{
		if (*it == clientFd)
		{
			_operators.erase(it);
			return ;
		}
	}
	return ;
}

// Informs whether or not this client is in the operator list
bool	Channel::isOperator(int clientFd) const {

	for (std::vector<int>::const_iterator it = _operators.begin(); it != _operators.end(); it++)
	{
		if (*it == clientFd)
			return (true);
	}
	return (false);
}