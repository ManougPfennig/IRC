#ifndef SERVERCLASS_H
# define SERVERCLASS_H

# include <iostream>
# include <iomanip>
# include <sstream>			
# include <string>
# include <limits>
# include <exception>
//struct serv, class des exceptions, retaper class client
class ServerActor {

	private:
		int			_serverSocket;
		int			_port;
		std::string _password;

	public:
		~ServerActor( void );
		ServerActor( void );
		ServerActor( const ServerActor &sa );
		ServerActor &operator=( const ServerActor &sa );

		// _serverSocket variable interaction

		int		getServerSocket( void ) const;
		void	setServerSocket( const int &socket );

		// _port variable interaction

		int		getPort( void ) const;
		void	setPort( const int &port );

		// _password variable interaction

		std::string	getPassword( void ) const;
		void		setPassword( const std::string &password );


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