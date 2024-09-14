#ifndef IRCSERV_H
# define IRCSERV_H

// Included Libraries

# include <iostream>
# include <iomanip>
# include <sstream>
# include <string>
# include <cstring>
# include <limits>
# include <exception>
# include <sys/socket.h>
# include <sys/select.h>

// Function Declaration List

int		parsing(int ac, char **av);
bool	isStrDigits(char *str)


// Macros

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

#endif