#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "ServerException.hpp"
# include <iostream>
# include <vector>
# include <map>

class Client {
	private:

		// Has Client finished registration ?
		bool	_registered;
		// Has Client entered the server password ?
		bool	_passed;
		// Is the client disconnecting ?
		bool	_quit;

		// Client information
		std::string	_nickname = "";
		std::string	_username = "";
		std::string _realname = "";

		// Unfinished command buffer
		std::string _buffer = "";

	public:

		~Client();
		Client();
		Client(const Client &sa);
		Client &operator=(const Client &sa);

		// Getters and Setters for private variable

		bool		getRegistered( void ) const;
		void		SetRegistered( bool registered );

		bool		getPassed( void ) const;
		void		SetPassed( bool passed );

		std::string	getNickname( void ) const;
		void		setNickname( std::string nickname);

		std::string	getUsername( void ) const;
		void		setUsername( std::string username);

		std::string	getRealname( void ) const;
		void		setRealname( std::string realname);

		void		setQuit( bool b );
		bool		getQuit( void ) const;

		void		setBuffer( std::string buf );
		std::string	getBuffer( void ) const;
		void		addToBuffer( std::string str );
		void		clearBuffer( void );

};

#endif