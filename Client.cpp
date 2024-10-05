#include "Client.hpp"

// Construction and Destruction scripts

Client::~Client( void ) {}

Client::Client( void ) : _registered(false), _passed(false), _quit(false) {}

Client::Client( const Client &sa ) : _registered(false), _passed(false), _quit(false) {}

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

void	Client::setQuit( bool b ) {

	_quit = b;
	return ;
}

bool	Client::getQuit( void ) const {

	return (_quit);
}

void		Client::setBuffer( std::string buf ) {

	_buffer = buf;
	return ;
}

std::string	Client::getBuffer( void ) const {

	return (_buffer);
}

void		Client::addToBuffer( std::string str ) {

	_buffer += str;
	return ;
}

void		Client::clearBuffer( void ) {

	_buffer.clear();
	return ;
}
