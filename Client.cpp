#include "Client.hpp"

Client::~Client( void ) {}

Client::Client( void ) {}

Client::Client( const Client &sa ) {
	for (int i = 0; _clientSocket[i]; i++) {
		_clientSocket[i] = sa._clientSocket[i];
	}
}

Client &Client::operator=( const Client &sa ) {
	for (int i = 0; _clientSocket[i]; i++) {
		_clientSocket[i] = sa._clientSocket[i];
	}
	return (*this);
}

int	Client::getSocket(int i) const {

	return (_clientSocket[i]);
}

void	Client::setSocket(int i, int socket) {

	_clientSocket[i] = socket;
	return ;
}

void	Client::initSocket() {
	for (int i = 0; i < MAXCLIENT; i++) {
        _clientSocket[i] = 0;
    }
}
