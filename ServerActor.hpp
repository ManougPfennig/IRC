#ifndef SERVERCLASS_H
# define SERVERCLASS_H

# include <iostream>
# include <iomanip>
# include <sstream>			
# include <string>
# include <limits>
# include <exception>

class ServerActor {

	private:
		int			_serverSocket;
		int			_port;
		std::string _password;

	public:
		int	_server_fd;

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

		int		getFd( void ) const;
		int		setFd(int fd);


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
			return ("Could not put the server socket inlistening mode...");
		}
	};

};

#endif