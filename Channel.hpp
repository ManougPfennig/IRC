#ifndef CHANNEL_HPP
# define CHANNEL_HPP

//# include "ircserv.hpp"
# include <iostream>
# include <vector>
# include <map>

class Channel {

	private:

		std::string					_name = "";
		std::string					_password = "";
		std::vector<int>			_clients;
		std::vector<int>			_operators;

		std::vector<std::string>	_invitedUsers;
		bool						_isInviteOnly;

		unsigned int				_usersLimit;
		bool						_hasUserLimit;

		std::string					_topic = "";
		bool						_topicSettableByUsers;


	public:

		~Channel();
		Channel();
		Channel(const std::string &name);
		Channel(const Channel &sa);
		Channel &operator=(const Channel &sa);

		// Getters and Setters for private variable
		std::string					getName( void ) const;
		void						setName( std::string name );

		std::vector<int>			&getClientsOfChannel();

		void						setPassword( std::string password );
		std::string					getPassword( void ) const;

		void						setInvitedUsers( std::vector<std::string> v );
		std::vector<std::string>	getInvitedUsers( void ) const ;

		void						setIsInvitOnly( bool b );
		bool						getIsInvitOnly( void ) const;

		void						setUsersLimit( unsigned int max );
		int							setUsersLimit( std::string max );
		unsigned int				getUsersLimit( void ) const;

		void						setHasUserLimit( bool b );
		bool						getHasUserLimit( void ) const;

		void						setTopic( std::string topic );
		std::string					getTopic( void ) const;

		void						setTopicSettableByUsers( bool b );
		bool						getTopicSettableByUsers( void );

		//utils
		void	addClientToChannel(int clientFd);
		void	removeClientFromChannel(int clientFd);
		bool	isClientInChannel(int clientFd);
		void	addOperator(int clientFd);
		void	removeOperator(int clientFd);
		bool	isOperator(int clientFd) const;
		void	addToInviteList( std::string username );
		void	removeFromInviteList( std::string username );
		bool	isInInviteList( std::string username ) const ;

};

#endif