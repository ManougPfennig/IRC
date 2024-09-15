#include "ServerActor.hpp"

ServerActor::~ServerActor( void ) {}

ServerActor::ServerActor( void ) {}

ServerActor::ServerActor( const ServerActor &sa ): _serverSocket(sa._serverSocket) {}

ServerActor &ServerActor::operator=( const ServerActor &sa ) {

	_serverSocket = sa._serverSocket;
	return (*this);
}

int	ServerActor::getSocket( void ) const {

	return (_serverSocket);
}

void	ServerActor::setSocket( int socket ) {

	_serverSocket = socket;
	return ;
}