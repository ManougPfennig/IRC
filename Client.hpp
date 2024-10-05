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
		// Is Client using hexchat ?
		bool	_xChat;

		bool	_quit;

		// Client information
		std::string	_nickname = "";
		std::string	_username = "";
		std::string _realname = "";

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
		bool		getQuit( void ) const ;

};

#endif