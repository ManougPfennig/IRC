#include "ircserv.hpp"

void	sendMsg( int fd, const char *str )
{
	send(fd, str, strlen(str), 0);
	return ;
}

// Returns true if C is in Charset, false otherwise.
bool	isInCharSet(char c, const char *charset)
{
	for (int i = 0; charset[i]; i++)
	{
		if (c == charset[i])
			return (true);
	}
	return (false);
}

// Checks whether the string is made entirely of numeric characters
bool isStrDigits( char *str )
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (isdigit(str[i]) == 0)
			return (false);
	}
	return (true);
}

// Displays a prompt to get an input string in the terminal
std::string	getInput( void )
{
	std::string	input;
	while (1)
	{
		input.clear();
		std::getline(std::cin, input);
		// Checks if stdin has been closed and returns empty input (error)
		if (feof(stdin) != 0)
		{
			std::cout << RED << "Closed stdin" << RESET << std::endl;
			return ("");
		}
		// Doesn't check entry if it is empty
		if (input.length() == 0)
			continue;
		else
			break;
	}
	return (input);
}

int	ft_sep(char c, const char *charset)
{
	int i = 0;
	while (charset[i] != '\0')
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

int	ft_word_number(char *str, const char *charset)
{
	int	i;
	int	number;

	i = 0;
	number = 0;
	while (str[i])
	{
		if (ft_sep(str[i + 1], charset) == 1
			&& ft_sep(str[i], charset) == 0)
			number++;
		i++;
	}
	return (number);
}

char	*ft_copy_word(char *dest, char *str, const char *charset)
{
	int	i;

	i = 0;
	while (ft_sep(str[i], charset) == 0)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_fill_tab(char **split, char *str, const char *charset)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (ft_sep(str[i], charset) == 1)
			i++;
		else
		{
			j = 0;
			while (ft_sep(str[i + j], charset) == 0)
				j++;
			split[count] = (char *)malloc(sizeof(char) * (j + 1));
			ft_copy_word(split[count], str + i, charset);
			i = i + j;
			count++;
		}
	}
}

char	**ft_split(const char *str, const char *charset)
{
	int		tab_len;
	char	**tab;

	if (!str)
		return (NULL);
	tab_len = ft_word_number((char *)str, charset);
	tab = (char **)malloc(sizeof(char *) * (tab_len + 1));
	if (!tab)
		return (NULL);
	tab[tab_len] = 0;
	ft_fill_tab(tab, (char *)str, charset);
	return (tab);
}

void	freeTab(char **tab)
{
	for (int i = 0; tab && tab[i]; i++)
		free(tab[i]);
	if (tab)
		free(tab);
	return ;
}

// Returns the associated Client instance to specified key in clientMap
Client	&gC(t_server *serv, int key)
{
	return (serv->clientMap.find(key)->second);
}

// Returns the associated client Fd to specified username in clientMap
// Returns -1 if client is not found
int			gC( t_server *serv, std::string name) {

	std::map<int, Client>::const_iterator it;

	for (it = serv->clientMap.begin(); it != serv->clientMap.end(); it++)
	{
		if (it->second.getUsername() == name)
			return (it->first);
	}
	return (-1);
}


// Will format the message according to Hexchat.
// - Set the variable "fromServer" to true if it should be displayed as coming from the server
// Returns ":ircserv code Username #channelName :message"
// - Set the variable "fromServer" to false if it should be displayed as coming from a user
// Returns ":Nickname!Username@ircserv command #channelName :message"
std::string formatMsg(t_server *serv, bool fromServer, int code,int clientFd, std::string command, std::string channelName, std::string message)
{
	std::string formattedMsg;

	if (fromServer == true)
	{
		formattedMsg = ":ircserv " + code + gC(serv, clientFd).getUsername() + " #" + channelName;
		if (!message.empty())
			formattedMsg += " :" + message;
		formattedMsg += "\r\n";
	}
	else
	{
		formattedMsg = ":" + gC(serv, clientFd).getNickname() + "!" + gC(serv, clientFd).getUsername() + "@ircserv " + command + " #" + channelName;
		if (!message.empty())
			formattedMsg += " :" + message;
		formattedMsg += "\r\n";
	}
	
	return (formattedMsg);
}

bool	doesChannelExist(t_server *serv, std::string channelName)
{
	if (serv->channelMap.find(channelName) == serv->channelMap.end())
		return (false);
	return (true);
}

// Checks whether or not if the string 'str' contains a char of type 'c'.
bool	contains(std::string str, char c)
{
	for (int i = 0; str[i]; i++) {
		if (str[i] == c)
			return (true);
	}
	return (false);
}
