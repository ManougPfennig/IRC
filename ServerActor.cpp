#include "ServerActor.hpp"

ServerActor::~ServerActor( void ) {}

ServerActor::ServerActor( void ) {}

ServerActor::ServerActor( const ServerActor &sa ): _serverSocket(sa._serverSocket) {}

ServerActor &ServerActor::operator=( const ServerActor &sa ) {

	_serverSocket = sa._serverSocket;
	return (*this);
}

// _serverSocket variable interaction

int	ServerActor::getServerSocket( void ) const {

	return (_serverSocket);
}

void	ServerActor::setServerSocket( const int &socket ) {

	_serverSocket = socket;
	return ;
}

// _port variable interaction

int	ServerActor::getPort( void ) const {

	return (_port);
}

void	ServerActor::setPort( const int &port ) {

	_port = port;
	return ;
}

// _password variable interaction

std::string	ServerActor::getPassword( void ) const {

	return (_password);
}

void	ServerActor::setPassword( const std::string &password ){

	_password = password;
	return ;
}
