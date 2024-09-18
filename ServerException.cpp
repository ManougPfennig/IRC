#include "ServerException.hpp"

ServerException::~ServerException( void ) {}

ServerException::ServerException( void ) {}

ServerException::ServerException( const ServerException &sa ) {}

ServerException &ServerException::operator=( const ServerException &sa ) {

	return (*this);
}
