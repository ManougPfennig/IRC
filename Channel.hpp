#ifndef CHANNEL_HPP
# define CHANNEL_HPP

//# include "ircserv.hpp"
# include <iostream>
# include <vector>
# include <map>

class Channel {
	private:

		std::string			_name = "";
		std::string			_password = "";
		std::string			_topic = "";
		std::vector<int>	_clients;
		std::vector<int>	_operators;

	public:

		~Channel();
		Channel();
		Channel(const std::string &name);
		Channel(const Channel &sa);
		Channel &operator=(const Channel &sa);

		// Getters and Setters for private variable
		std::string			getName( void ) const;
		void				setName( std::string name);
		std::vector<int>	&getClientsOfChannel();
		void				setPassword(std::string password);
		std::string			getPassword(void) const;
		void				setTopic(std::string topic);
		std::string			getTopic(void) const;

		//utils
		void	addClientToChannel(int clientFd);
		void	removeClientFromChannel(int clientFd);
		bool	isClientInChannel(int clientFd);
		void	addOperator(int clientFd);
		void	removeOperator(int clientFd);
		bool	isOperator(int clientFd) const;

};

#endif