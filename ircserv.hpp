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

# include "ServerActor.hpp"

// -------------------------
// FUNCTION DECLARATION LIST
// -------------------------

int			parsing( int ac, char **av );
bool		isStrDigits( char *str );
std::string	getInput( void );
void		openServer( ServerActor &serv );

// Messages Printing

void		displayLaunchExemple( void );
void		printPortHelp( void );


// -------------------------
// MACROS
// -------------------------

// Values

# define ERROR 1
# define ALLGOOD 0

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

# define PASSHELPMESSAGE "Password should be at least one character long."

#endif