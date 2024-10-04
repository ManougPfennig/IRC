#ifndef IRCSERV_H
# define IRCSERV_H

// -------------------------
// INCLUDED LIBRARIES
// -------------------------

# include <iostream>
# include <iomanip>
# include <sstream>			
# include <string>
# include <limits>
# include <exception>
# include <map>
# include <vector>
# include <sstream>

# include <sys/select.h>	// For select()
# include <sys/types.h>		// For socket(), fstat()
# include <sys/socket.h>	// For socket(), setsockopt(), getsockname(), bind(), listen(), accept()
# include <netinet/in.h>	// For htons(), htonl(), ntohs(), ntohl(), struct sockaddr_in
# include <arpa/inet.h>		// For inet_addr(), inet_ntoa(), gethostbyname(), getaddrinfo(), freeaddrinfo()
# include <unistd.h>		// For close(), read(), write(), lseek()
# include <netdb.h>			// For getprotobyname(), gethostbyname(), getaddrinfo(), freeaddrinfo()
# include <fcntl.h>			// For fcntl()
# include <signal.h>		// For signal(), sigaction()
# include <cstring>			// For memset(), strerror()

# include "ServerException.hpp"
# include "Client.hpp"
# include "Channel.hpp"

// -------------------------
// MACROS
// -------------------------

// Values

# define ERROR 1
# define ALLGOOD 0
# define BUFFERSIZE 1024
# define MAXCLIENT 100

// Terminal Text Colors

# define RESET   "\033[0m"
# define RED     "\033[31m"      
# define GREEN   "\033[32m"      
# define YELLOW  "\033[33m"      
# define BLUE    "\033[34m"      
# define MAGENTA "\033[35m"      
# define CYAN    "\033[36m"      
# define WHITE   "\033[37m"

// Help Messages

# define PORTHELPMESSAGE "The ports 6660-6669, 6697, 7000-7005, 8000-8005, 9999 are commonly used ports for IRC servers but theoretically any port\n\
in the range of 1 to 65535 can be used, as long as the port isn't already in use by another service on the system.\n\
Avoid reserved ports (0-1023): These are reserved for system services like HTTP (80), SSH (22), and others.\n\
Any port between 1024 and 65535 should do."

# define PASSHELPMESSAGE "Password should not contain whitespaces."

# define AUTH_MESSAGE "Register using 'PASS ...' then 'NICK ...' then 'USER ...'\n"


// -------------------------
// SERVER INFORMATION STRUCTURE
// -------------------------

typedef struct	s_serverinfo {

	std::string			password;

	int					port = 0;
	int					server_fd = 0;
	int					nfds = 0;
	int					activity = 0;
	int					new_client = 0;
	int					valueread = 0;
	int					serverSocket = 0;
	int					addrlen = 0;

	fd_set				readfds;
	fd_set				writefds;
	fd_set				exceptfds;

	struct sockaddr_in6	address6;

	char				buffer[BUFFERSIZE];

	std::map<int, Client>			clientMap;
	std::map<std::string, Channel>	channelMap;

}				t_server;

typedef struct	s_channelInfo {

	std::string	name;

}				t_channel;

typedef struct	s_commandInfo {

	std::string	cmd;
	std::string	arg;

}				t_cmd;


// -------------------------
// FUNCTION DECLARATION LIST
// -------------------------

// server operation
int		parsing( int ac, char **av );
void	openServer( t_server *serv, char *port, char *password );
void	serverLoop( t_server *serv );
void	messageParsing( t_server *serv );
void	clientRegistration( t_server *serv, int clientFd );
void	registerNewClient(t_server *serv, int);
void	sendMsg( int fd, const char *str );
void	cmdsParse(t_server *serv, int clientFd, std::string toParse);
void	broadcastToChannel(t_server *serv, std::string channelName, int senderFd, std::string msg);
void	disconnectClientFromChannel(t_server *serv, int clientFd, std::string &channelName, std::string msg);
void	broadcastLeaving(t_server *serv, std::string channelName, int senderFd, std::string msg);
void	broadcastKick(t_server *serv, std::string channelName, int senderFd, int targetFd, std::string msg);
void	broadcastJoining(t_server *serv, std::string channelName, int senderFd);
void	cleanChannelsFromDisconnectingClients(t_server *serv, int clientFd);

// Commands
void	PASS( t_server *serv, int key, std::string arg );
void	NICK( t_server *serv, int key, std::string arg );
void	USER( t_server *serv, int key, std::string arg );
void	QUIT( t_server *serv, int key, std::string arg );
void	PART( t_server *serv, int clientFd, std::string channelName, std::string msg );
void	JOIN( t_server *serv, int clientFd, std::string channelName, std::string password );
void	KICK( t_server *serv, int clientFd, std::string channelName, std::string arg );
void	MODE( t_server *serv, int clientFd, std::string channelName, std::string arg );
void	INVITE( t_server *serv, int clientFd, std::string username, std::string arg );

// utils
std::string	getInput( void );
bool		isStrDigits( char *str );
char		**ft_split( const char *str, const char *charset );
void		freeTab( char **tab );
bool		isInCharSet(char c, const char *charset);
Client		&gC(t_server *serv, int key);
int			gC(t_server *serv, std::string name);
int			whichCommand(std::string cmd);
bool		doesChannelExist(t_server *serv, std::string channelName);
std::string formatMsg(t_server *serv, bool fromServer, int code, int clientFd, std::string command, std::string channelName, std::string message);
bool		contains(std::string str, char c);
bool		isUsernameTaken(t_server *serv, std::string name);
int			isChannelNameAChannel(t_server *serv, std::string channelName);
void		sendPrivateMessage(t_server *serv, std::string channelName, int clientFd, std::string arg);


// Messages Printing

// void		displayLaunchExemple( void );
// void		printPortHelp( void );


extern const char	*cmdType[];

#endif