#include "Client.hpp"

// Construction and Destruction scripts

Client::~Client( void ) {}

Client::Client( void ) : _registered(false), _passed(false), _xChat(false) {}

Client::Client( const Client &sa ) : _registered(false), _passed(false), _xChat(false) {}

// = Operator overcharge

Client &Client::operator=( const Client &sa ) {

	return (*this);
}

// Getters and Setters

bool		Client::getRegistered( void ) const{

	return (_registered);
}

void		Client::SetRegistered( bool registered ){

	_registered = registered;
	return ;
}

bool		Client::getPassed( void ) const{

	return (_passed);
}

void		Client::SetPassed( bool passed ){

	_passed = passed;
	return ;
}

std::string	Client::getNickname( void ) const{

	return (_nickname);
}

void		Client::setNickname( std::string nickname){

	_nickname = nickname;
	return ;
}

std::string	Client::getUsername( void ) const{

	return (_username);
}

void		Client::setUsername( std::string username){

	_username = username;
	return ;
}

std::string	Client::getRealname( void ) const{

	return (_realname);
}

void		Client::setRealname( std::string realname){

	_realname = realname;
	return ;
}
