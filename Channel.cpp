#include "Channel.hpp"

// Construction and Destruction scripts

Channel::~Channel( void ) {}

Channel::Channel( void ) : _isInviteOnly(false), _topicSettableByUsers(false), _usersLimit(0), _hasUserLimit(false) {}

Channel::Channel(const std::string &name) : _name(name), _isInviteOnly(false), _topicSettableByUsers(false), _usersLimit(0), _hasUserLimit(false) {}

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

void						Channel::setInvitedUsers( std::vector<std::string> v ) {

	_invitedUsers = v;
	return ;
}

std::vector<std::string>	Channel::getInvitedUsers( void ) const {

	return (_invitedUsers);
}

void				Channel::setIsInviteOnly( bool b ){

	_isInviteOnly = b;
	return ;
}

bool				Channel::getIsInviteOnly( void ) const{

	return (_isInviteOnly);
}

void				Channel::setUsersLimit( unsigned int max ){

	_usersLimit = max;
	return ;
}

int					Channel::setUsersLimit( std::string max ){

	// Check if input string is not empty
	if (max.empty())
		return (1);

	// Check if all characters are digits
	for (int i = 0; max[i]; i++) {
		if (isdigit(max[i]) == 0)
			return (1);
	}
	// Check if value is not over unsigned int max
	if ((unsigned int)atol(max.c_str()) > UINT32_MAX)
		return (1);

	// Set user's limit new value
	_usersLimit = (unsigned int)atol(max.c_str());
	return (0);
}

unsigned int		Channel::getUsersLimit( void ) const{

	return (_usersLimit);
}

void				Channel::setHasUserLimit( bool b ){

	_hasUserLimit = b;
	return ;
}
bool				Channel::getHasUserLimit( void ) const{

	return (_hasUserLimit);
}

void				Channel::setTopic(std::string topic) {

	_topic = topic;
	return ;
}

std::string			Channel::getTopic(void) const {

	return (_topic);
}

void				Channel::setTopicSettableByUsers( bool b ){

	_topicSettableByUsers = b;
	return ;
}

bool				Channel::getTopicSettableByUsers( void ){

	return (_topicSettableByUsers);
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
			break ;
		}
	}

	// remove from _operators
	for (std::vector<int>::iterator it = _operators.begin(); it != _operators.end(); it++){
		if (*it == clientFd){
			_operators.erase(it);
			break ;
		}
	}
	return ;
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
			break ;
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

// Adds a username to the list of invited users
void	Channel::addToInviteList( std::string username ) {

	_invitedUsers.push_back(username);
	return ;
}

void	Channel::removeFromInviteList( std::string username ) {

	std::vector<std::string>::const_iterator it;
	for (it = _invitedUsers.begin(); it != _invitedUsers.end(); it++) {

		if (*it == username)
		{
			_invitedUsers.erase(it);
			break ;
		}
	}
	return ;
}

// Checks whether or not a user is in the list of invited users
bool	Channel::isInInviteList( std::string username ) const {

	std::vector<std::string>::const_iterator it;

	for (it = _invitedUsers.begin(); it != _invitedUsers.end(); it++) {

		if (*it == username)
			return (true);
	}
	return (false);
}
