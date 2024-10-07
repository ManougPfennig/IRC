#include "ircserv.hpp"

const char	*answers[] = {

	// Affirmative Answers
	"It is certain",
	"It is decidedly so",
	"Without a doubt",
	"Yes definitely",
	"You may rely on it",
	"As I see it, yes",
	"Most likely",
	"Outlook good",
	"Yes",
	"Signs point to yes",

	// Non – Committal Answers
	"Reply hazy, try again",
	"Ask again later",
	"Better not tell you now",
	"Cannot predict now",
	"Concentrate and ask again",

	// Negative Answers
	"Don't count on it",
	"My reply is no",
	"My sources say no",
	"Outlook not so good",
	"Very doubtful",
	NULL,
};

std::string	get8ballAnswer( void ) {

	return (answers[rand() % 20]);
}

void	ask8ball(t_server *serv, std::string channelName) {

	// Getting the list of clients on the channel
	std::vector<int>	&clients = serv->channelMap[channelName].getClientsOfChannel();

	// Then a formatted answer message is broadcasted to all clients in the channel
	std::string	msg = ":Magic8Ball!Magic8Ball@ircserv PRIVMSG #" + channelName + " :" + get8ballAnswer() + ".\r\n";
	for (std::vector<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
		sendMsg(*it, msg.c_str());
	}

	return ;
}