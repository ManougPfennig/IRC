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
		int	_serverSocket;
		int	_port;

	public:

		~ServerActor( void );
		ServerActor( void );
		ServerActor( const ServerActor &sa );
		ServerActor &operator=( const ServerActor &sa );

		int		getSocket( void ) const;
		void	setSocket( int socket );


	class SocketCreationFailed : public std::exception
	{
		const char *what() const throw()
		{
			return ("Could not open a new socket");
		}
	};

};

#endif