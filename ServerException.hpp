#ifndef SERVEREXCEPTION_H
# define SERVEREXCEPTION_H

# include <iostream>
# include <iomanip>
# include <sstream>			
# include <string>
# include <limits>
# include <exception>

class ServerException {

	private:

	public:
		~ServerException( void );
		ServerException( void );
		ServerException( const ServerException &sa );
		ServerException &operator=( const ServerException &sa );

	class SocketCreationFailed : public std::exception
	{
		const char *what() const throw()
		{
			return ("Could not open a new socket...");
		}
	};
	class SocketBindingFailed : public std::exception
	{
		const char *what() const throw()
		{
			return ("Could not bind the server socket...");
		}
	};
	class SocketListeningFailed : public std::exception
	{
		const char *what() const throw()
		{
			return ("Could not put the server socket in listening mode...");
		}
	};
	class SelectFailed : public std::exception
	{
		const char *what() const throw()
		{
			return ("[SELECT ERROR] Something wrong happened, please try again...");
		}
	};
	class ClientAcceptFailed : public std::exception
	{
		const char *what() const throw()
		{
			return ("[CLIENT ACCEPT()] Something wrong happened, please try again...");
		}
	};
};

#endif